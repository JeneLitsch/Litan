#include "Ltnc.hxx"
#include <vector>
#include <iostream>
#include "parse/parse.hxx"
#include "optimize/optimize.hxx"
#include "assemble/assemble.hxx"
#include <string_view>

#include "compile/compile.hxx"
#include <iostream>
#include "print/print.hxx"

using namespace std::string_view_literals;

namespace ltn::c {
	ast::Source parse(
		Tokens & tokens,
		Reporter & reporter) {
		
		return parse_source(tokens, reporter);
	}

	Tokens tokenize(
		std::vector<Source> sources,
		Reporter & reporter) {

		return lex::lex_sources(std::move(sources), reporter);
	}
}




namespace ltn::c {
	namespace {
		sst::Var accessor(const sst::Definition & def) {
			return sst::Var {
				def.name,
				def.namespaze,
				def.location
			};
		}

		sst::GlobalVar accessor(const sst::Global & def) {
			return sst::GlobalVar {
				def.location,
				def.namespaze,
				def.name
			};
		}


		InstructionBuffer static_init(
			auto & read_info,
			auto & write_info,
			auto & statics,
			auto & compile_write) {
			


			InstructionBuffer buf;
			for(const auto & s : statics) {
				if(s->expr) {
					MajorScope scope { s->namespaze, false };
					const auto a = accessor(*s);
					buf << compile_expression(*s->expr, read_info, scope).code;
					buf << compile_write(a, write_info, scope).code;
				}
			}

			return buf;
		}

		
		InstructionBuffer global_init(auto & info, auto & globals) {
			// Use empty global_table to prohibit the usage of other global variables.
			// Functions or defines can be used though.
			InvalidGlobalTable global_table { "the default value of another global variable" };
			InvalidFunctionTable fx_table { "the initialization of a global variable" };
			InvalidFunctionTemplateTable fx_template_table { "the initialization of a global variable" };
			CompilerInfo read_info {
				.fx_table          = fx_table,
				.fx_template_table = fx_template_table,
				.fx_queue		   = info.fx_queue,
				.definition_table  = info.definition_table,
				.member_table      = info.member_table,
				.global_table      = global_table,
				.reporter          = info.reporter
			};

			auto & write_info = info;

			return static_init(read_info, write_info, globals, compile_write_global);
		}

		
		
		InstructionBuffer define_init(auto & info, auto & globals) {
			// Use empty global_table to prohibit the usage of other global variables.
			// Functions or defines can be used though.
			InvalidDefinitionTable def_table { "definitions" };
			InvalidGlobalTable global_table { "definitions" };
			InvalidFunctionTable fx_table { "definitions" };
			InvalidFunctionTemplateTable fx_template_table { "definitions" };
			CompilerInfo read_info {
				.fx_table          = fx_table,
				.fx_template_table = fx_template_table,
				.fx_queue		   = info.fx_queue,
				.definition_table  = def_table,
				.member_table      = info.member_table,
				.global_table      = global_table,
				.reporter          = info.reporter
			};

			auto & write_info = info;

			return static_init(read_info, write_info, globals, compile_write_define);
		}


		std::vector<stx::reference<const sst::Functional>> find_extern_funtions(
			const sst::Program & program) {
			std::vector<stx::reference<const sst::Functional>> externs;
			for(const auto & fx : program.functions) {
				if(fx->init) {
					externs.push_back(*fx);
				}
				if(fx->name == "main" && (fx->parameters.size() == 0 || fx->parameters.size() == 1)) {
					externs.push_back(*fx);
				}
			}
			return externs;
		}



		InstructionBuffer compile_staged(const StagedFx & staged, CompilerInfo & info) {
			return compile_functional(*staged.fx, info); 
		}

		InstructionBuffer compile_staged(const StagedTemplateFx & staged, CompilerInfo & info) {
			return compile_function_template(staged.tmpl, info, staged.arguments); 
		}
	}


	sst::Program analyze(
		const ast::Source & source,
		Reporter & reporter) {
		
		sst::Program program;
		ValidFunctionTable fx_table;
		FunctionQueue fx_queue;
		ValidFunctionTemplateTable fx_template_table;
		ValidDefinitionTable definition_table;
		MemberTable member_table;
		ValidGlobalTable global_table;
		CompilerInfo info {
			.fx_table = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue = fx_queue,
			.definition_table = definition_table,
			.member_table = member_table,
			.global_table = global_table,
			.reporter = reporter,
		};


		for(auto & preset : source.presets) {
			auto ctor = analyze_preset(*preset);
			program.functions.push_back(std::move(ctor));
		}

		for(auto & enym : source.enums) {
			auto definitions = analyze_enumeration(*enym);
			for(auto & definition : definitions) {
				program.definitions.push_back(std::move(definition));
			}
		}

		for(const auto & definition : source.definitions) {
			program.definitions.push_back(analyze_definition(*definition, info));
		}

		for(const auto & global : source.globals) {
			program.globals.push_back(analyze_global(*global, info));
		}

		for(const auto & fx_tmpl : source.function_templates) {
			program.function_templates.push_back(analyze_function_template(*fx_tmpl, info));
		}

		for(const auto & fx : source.functions) {
			program.functions.push_back(analyze_functional(*fx, info));
		}

		return program;
	}

	// compiles source
	Instructions compile(
		const sst::Program & program,
		Reporter & reporter) {
		
		InstructionBuffer buf;
		ValidFunctionTable fx_table;
		FunctionQueue fx_queue;
		ValidFunctionTemplateTable fx_template_table;
		ValidDefinitionTable definition_table;
		MemberTable member_table;
		ValidGlobalTable global_table;
		CompilerInfo info {
			.fx_table = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue = fx_queue,
			.definition_table = definition_table,
			.member_table = member_table,
			.global_table = global_table,
			.reporter = reporter,
		};


		for(const auto & definition : program.definitions) {
			info.definition_table.insert(*definition);
		}
		buf << define_init(info, program.definitions);

		for(const auto & global : program.globals) {
			info.global_table.insert(*global);
		}
		buf << global_init(info, program.globals);

		for(const auto & fx_tmpl : program.function_templates) {
			const auto function_arity = std::size(fx_tmpl->fx->parameters);
			const auto template_arity = std::size(fx_tmpl->template_parameters);
			info.fx_template_table.insert(*fx_tmpl, function_arity, template_arity);
		}

		for(const auto & fx : program.functions) {
			info.fx_table.insert(*fx, std::size(fx->parameters));
		}


		// buf << static_init(info, program.definitions);
		buf << inst::null();
		buf << inst::exit();
		
		auto externs = find_extern_funtions(program);

		for(const auto & function : externs) {
			fx_queue.stage_function(function);
		}

		while(auto staged = fx_queue.fetch_function()) {
			try {
				buf << std::visit([&] (auto & s) {
					return compile_staged(s, info); },
				*staged);
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}

		std::set<std::string> extern_functions;
		extern_functions.insert("main(0)");
		extern_functions.insert("main(1)");
		for(const auto & fx : program.functions) {
			if(fx->init) extern_functions.insert(fx->id);
		}

		AddressTable extern_globals;
		for(const auto symbol : global_table.get_symbols()) {
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