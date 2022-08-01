#include "Ltnc.hxx"
#include <vector>
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
		
		auto source = parse_source(tokens);
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
		InstructionBuffer init_static_construct(auto & read_info, auto & write_info, auto & obj) {
			InstructionBuffer buf;
			Scope scope{obj.namespaze, false};
			const ast::GlobalVar global_var {
				obj.namespaze,
				obj.name,
				obj.location
			};
			buf << compile_expression(*obj.expr, read_info, scope).code;
			buf << compile_write_global(global_var, write_info, scope).code;
			return buf;
		}

		InstructionBuffer static_init(auto & info, auto & statics) {
			// Use empty global_table to prohibit the usage of other global variables.
			// Functions or defines can be used though.
			GlobalTable global_table;
			FxTable fx_table;
			CompilerInfo read_info {
				.fx_table         = fx_table,
				.definition_table = info.definition_table,
				.member_table     = info.member_table,
				.global_table     = global_table,
				.reporter         = info.reporter
			};

			auto & write_info = info;

			InstructionBuffer buf;
			for(const auto & s : statics) {
				if(s->expr) {
					buf << init_static_construct(read_info, write_info, *s);
				}
			}

			return buf;
		}
	}

	// compiles source
	Instructions compile(
		const ast::Program & program,
		Reporter & reporter) {
		
		InstructionBuffer buf;
		DefinitionTable definition_table;
		FxTable fx_table;
		MemberTable member_table;
		GlobalTable global_table;
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

		for(const auto & global : program.globals) {
			info.global_table.insert(*global);
		}

		for(const auto & fx : program.functions) {
			info.fx_table.insert(*fx);
		}


		// buf << static_init(info, program.definitions);
		buf << static_init(info, program.globals);
		buf << inst::Null{};
		buf << inst::Exit{};

		for(const auto & function : program.functions) {
			try {
				buf << compile_functional(*function, info); 
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}

		std::set<std::string> init_functions;
		init_functions.insert("main(0)");
		init_functions.insert("main(1)");
		for(const auto & fx : program.functions) {
			if(fx->init) init_functions.insert(fx->id);
		}

		buf << inst::Exit{};

		return {
			buf.get(),
			init_functions,
		};
	}


	std::vector<std::uint8_t> assemble(
		const Instructions & instructions) {		
		const auto jump_table = scan(instructions.insts);

		std::unordered_map<std::string, std::uint64_t> fx_table;

		for(const auto & fx_id : instructions.init_functions) {
			if(jump_table.contains(fx_id)) {
				fx_table[fx_id] = jump_table.at(fx_id);
			}
		}

		const auto bytecode = assemble(instructions.insts, jump_table, fx_table);
		return bytecode;
	}
}