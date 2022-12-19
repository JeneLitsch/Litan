#include "Ltnc.hxx"
#include <vector>
#include <iostream>
#include "parse/parse.hxx"
#include "optimize/optimize.hxx"
#include "assemble/assemble.hxx"
#include <string_view>

#include "compile/compile.hxx"
#include "analyze/analyze.hxx"
#include <iostream>
#include "print/print.hxx"

using namespace std::string_view_literals;

namespace ltn::c {
	ast::Program parse(
		Tokens & tokens,
		Reporter & reporter) {
		
		return parse_source(tokens, reporter);
	}

	Tokens tokenize(
		std::vector<std::unique_ptr<Source>> sources,
		Reporter & reporter) {

		return lex::lex_sources(sources, reporter);
	}
}




namespace ltn::c {
	namespace {
		InstructionBuffer static_init(auto & statics) {

			InstructionBuffer buf;
			for(const auto & s : statics) {
				if(s->expr) {
					buf << compile_expression(*s->expr);
					buf << inst::global_write(s->id);
				}
			}

			return buf;
		}


		std::vector<stx::reference<const ast::Functional>> find_extern_funtions(
			const ast::Program & source) {
			std::vector<stx::reference<const ast::Functional>> externs;
			for(const auto & fx : source.functions) {
				if(fx->init) {
					externs.push_back(*fx);
				}
				if(fx->name == "main" && (fx->parameters.size() == 0 || fx->parameters.size() == 1)) {
					externs.push_back(*fx);
				}
			}
			return externs;
		}



		auto analyze_staged(const StagedFx & staged, Context & context) {
			// std::cout << staged.fx->id << "\n";
			return analyze_functional(*staged.fx, context); 
		}

		auto analyze_staged(const StagedTemplateFx & staged, Context & context) {
			// std::cout << staged.tmpl->fx->id << "\n";
			return analyze_function_template(staged.tmpl, context, staged.arguments); 
		}
	}


	sst::Program analyze(
		const ast::Program & source,
		Reporter & reporter) {
		
		sst::Program program;
		ValidFunctionTable fx_table;
		FunctionQueue fx_queue;
		ValidFunctionTemplateTable fx_template_table;
		ValidDefinitionTable definition_table;
		MemberTable member_table;
		ValidGlobalTable global_table;
		Context context {
			.fx_table = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue = fx_queue,
			.definition_table = definition_table,
			.member_table = member_table,
			.global_table = global_table,
			.reporter = reporter,
		};



		for(auto & enym : source.enums) {
			auto definitions = analyze_enumeration(*enym);
			for(auto & definition : definitions) {
				program.definitions.push_back(std::move(definition));
			}
		}

		for(const auto & definition : source.definitions) {
			program.definitions.push_back(analyze_definition(*definition, context));
		}

		for(const auto & def : program.definitions) {
			context.definition_table.insert(*def);
		}



		for(const auto & global : source.globals) {
			program.globals.push_back(analyze_global(*global, context));
		}

		for(const auto & glob : program.globals) {
			context.global_table.insert(*glob);
		}


		std::vector<ast::func_ptr> ctors;
		for(auto & preset : source.presets) {
			auto ctor = generate_ctor(*preset);
			ctors.push_back(std::move(ctor));
		}

		for(const auto & fx_tmpl : source.function_templates) {
			const auto function_arity = std::size(fx_tmpl->fx->parameters);
			const auto template_arity = std::size(fx_tmpl->template_parameters);
			context.fx_template_table.insert(*fx_tmpl, function_arity, template_arity);
		}

		for(const auto & function : source.functions) {
			context.fx_table.insert(*function, function->parameters.size());
		}

		for(const auto & ctor : ctors) {
			context.fx_table.insert(*ctor, ctor->parameters.size());
		}

		auto externs = find_extern_funtions(source);

		for(const auto & function : externs) {
			fx_queue.stage_function(function);
		}

		while(auto staged = fx_queue.fetch_function()) {
			try {
				auto fx = std::visit([&] (auto & s) {
					return analyze_staged(s, context);
					}, *staged
				);
				program.functions.push_back(std::move(fx));
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}

		return program;
	}

	// compiles source
	Instructions compile(
		const sst::Program & program,
		Reporter &) {
		
		InstructionBuffer buf;

		buf << static_init(program.definitions);
		buf << static_init(program.globals);


		// buf << static_init(context, program.definitions);
		buf << inst::null();
		buf << inst::exit();
		
		for(const auto & function : program.functions) {
			buf << compile_functional(*function);
		}


		std::set<std::string> extern_functions;
		extern_functions.insert("main(0)");
		extern_functions.insert("main(1)");
		for(const auto & fx : program.functions) {
			if(fx->init) extern_functions.insert(fx->id);
		}

		AddressTable extern_globals;
		for(const auto & symbol : program.globals) {
			const auto full_name = symbol->namespaze.to_string() + symbol->name;
			extern_globals.insert({full_name, symbol->id});
		}


		buf << inst::exit();

		return {
			buf.get(),
			extern_functions,
			extern_globals
		};
	}


	namespace {
		AddressTable build_fx_table(
			const std::set<std::string> & fx_ids,
			const AddressTable & jump_table) {
			
			AddressTable function_table;
			for(const auto & fx_id : fx_ids) {
				if(jump_table.contains(fx_id)) {
					function_table[fx_id] = jump_table.at(fx_id);
				}
			}
			return function_table;
		}
	}


	std::vector<std::uint8_t> assemble(
		const Instructions & instructions) {
		
		const auto jump_table     = scan(instructions.insts);
		const auto function_table = build_fx_table(instructions.init_functions, jump_table);
		const auto global_table   = instructions.global_table;

		const auto bytecode = assemble(instructions.insts, jump_table, function_table, global_table);
		return bytecode;
	}
}