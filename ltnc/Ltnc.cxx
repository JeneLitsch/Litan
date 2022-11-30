#include "Ltnc.hxx"
#include <vector>
#include <iostream>
#include "parse/parse.hxx"
#include "unfold/unfold.hxx"
#include "optimize/optimize.hxx"
#include "assemble/assemble.hxx"
#include <string_view>

#include "compile/compile.hxx"
#include <iostream>
#include "print/print.hxx"

using namespace std::string_view_literals;

namespace ltn::c {
	ast::Program parse(
		Tokens & tokens,
		Reporter & reporter) {
		
		auto source = parse_source(tokens, reporter);
		return std::move(*unfold_source(std::move(source)));
	}

	Tokens tokenize(
		std::vector<Source> sources,
		Reporter & reporter) {

		return lex::lex_sources(std::move(sources), reporter);
	}
}




namespace ltn::c {
	namespace {
		ast::Var accessor(const ast::Definition & def) {
			return ast::Var {
				def.name,
				def.namespaze,
				def.location
			};
		}

		ast::GlobalVar accessor(const ast::Global & def) {
			return ast::GlobalVar {
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
			InvalidFunctionTable fx_table { "the initialization of a global variables" };
			CompilerInfo read_info {
				.fx_table         = fx_table,
				.definition_table = info.definition_table,
				.member_table     = info.member_table,
				.global_table     = global_table,
				.reporter         = info.reporter
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
			CompilerInfo read_info {
				.fx_table         = fx_table,
				.definition_table = def_table,
				.member_table     = info.member_table,
				.global_table     = global_table,
				.reporter         = info.reporter
			};

			auto & write_info = info;

			return static_init(read_info, write_info, globals, compile_write_define);
		}
	}

	// compiles source
	Instructions compile(
		const ast::Program & program,
		Reporter & reporter) {
		
		InstructionBuffer buf;
		ValidDefinitionTable definition_table;
		ValidFunctionTable fx_table;
		MemberTable member_table;
		ValidGlobalTable global_table;
		CompilerInfo info {
			.fx_table = fx_table,
			.definition_table = definition_table,
			.member_table = member_table,
			.global_table = global_table,
			.reporter = reporter
		};




		for(const auto & definition : program.definitions) {
			info.definition_table.insert(*definition);
		}
		buf << define_init(info, program.definitions);

		for(const auto & global : program.globals) {
			info.global_table.insert(*global);
		}
		buf << global_init(info, program.globals);

		for(const auto & fx : program.functions) {
			info.fx_table.insert(*fx, std::size(fx->parameters));
		}


		// buf << static_init(info, program.definitions);
		buf << inst::null();
		buf << inst::exit();

		for(const auto & function : program.functions) {
			try {
				buf << compile_functional(*function, info); 
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