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
			fx_table,
			definition_table,
			member_table,
			global_table,
			reporter};

		for(const auto & fx : program.functions) {
			info.fx_table.insert(*fx);
		}

		for(const auto & definition : program.definitions) {
			info.definition_table.insert(*definition);
		}

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