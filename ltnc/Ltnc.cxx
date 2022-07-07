#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parse.hxx"
#include "unfold/unfold.hxx"
#include "optimize/optimize.hxx"
#include "assemble/assemble.hxx"
#include <string_view>
#include "stdlib/algorithm.hxx"
#include "stdlib/bits.hxx"
#include "stdlib/cast.hxx"
#include "stdlib/chrono.hxx"
#include "stdlib/container.hxx"
#include "stdlib/debug.hxx"
#include "stdlib/functional.hxx"
#include "stdlib/io.hxx"
#include "stdlib/math.hxx"
#include "stdlib/random.hxx"
#include "stdlib/range.hxx"
#include "stdlib/type.hxx"
#include "compile/compile.hxx"
#include <iostream>
#include "print/print.hxx"

using namespace std::string_view_literals;

namespace ltn::c {
	ast::Program parse(
		std::vector<Source> sources,
		Reporter & reporter) {
		ast::Program program;
		
		auto parse = [&program, &reporter] (
			std::istream & in,
			const std::string & sourcename) {
			
			lex::Lexer lexer{in, sourcename, reporter};
			try {
				auto source = parse_source(lexer);
				auto t_unit = unfold_source(std::move(source));
				for(auto && fx : t_unit->functions) {
					program.functions.push_back(std::move(fx));
				}

				for(auto && e : t_unit->globals) {
					program.globals.push_back(std::move(e));
				}
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		};
		
		auto parse_std = [&parse](auto code) {
			std::istringstream iss{code};
			parse(iss, "");
		};

		parse_std(std_algorithm);
		parse_std(std_bits);
		parse_std(std_cast);
		parse_std(std_chrono);
		parse_std(std_container);
		parse_std(std_debug);
		parse_std(std_functional);
		parse_std(std_io);
		parse_std(std_math);
		parse_std(std_random);
		parse_std(std_range);
		parse_std(std_type);

		for(auto & source : sources) {
			parse(source.stream(), source.name());
		}

		return program;
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