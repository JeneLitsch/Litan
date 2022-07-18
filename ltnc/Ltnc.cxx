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
		InstructionBuffer startup_code(FxTable & fx_table) {
			// Jump to main()
			if(const auto fxmain = fx_table.resolve("main", {}, 0)) {
				InstructionBuffer buf;
				buf << ltn::inst::Call{fxmain->id};
				buf << ltn::inst::Exit{};
				return buf;
			}
			// Jump to main()
			else if(const auto fxmain = fx_table.resolve("main", {}, 1)) {
				InstructionBuffer buf;
				buf << ltn::inst::Call{fxmain->id};
				buf << ltn::inst::Exit{};
				return buf;
			}
			else {
				throw CompilerError {"main() is undefined", {}};
			}
		}
	}

	// compiles source
	std::vector<ltn::inst::Instruction> compile(
		const ast::Program & program,
		Reporter & reporter) {
		
		InstructionBuffer buf;
		GlobalTable global_table;
		FxTable fx_table;
		MemberTable member_table;
		CompilerInfo info {
			fx_table,
			global_table,
			member_table,
			reporter};

		for(const auto & fx : program.functions) {
			info.fx_table.insert(*fx);
		}

		for(const auto & global : program.globals) {
			info.global_table.insert(*global);
		}

		try {
			buf << startup_code(fx_table);
		}
		catch(const CompilerError & error) {
			reporter.push(error);
		}

		for(const auto & function : program.functions) {
			try {
				buf << compile_functional(*function, info); 
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}

		return buf.get();
	}


	std::vector<std::uint8_t> assemble(const std::vector<inst::Instruction> & instructions) {		
		const auto jump_table = scan(instructions);
		const auto bytecode = assemble(instructions, jump_table);
		return bytecode;
	}
}