#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parse.hxx"
#include "unfold/unfold.hxx"
#include "optimize/optimize.hxx"
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

using namespace std::string_view_literals;

namespace ltn::c {



	ast::Program parse(
		std::vector<Source> sources,
		const Config & config,
		Reporter & reporter) {
		ast::Program program;
		
		auto parse = [&program, &reporter] (
			std::istream & in,
			const std::string & sourcename) {
			
			lex::Lexer lexer{in, sourcename, reporter};
			try {
				auto source = parse_source(lexer);
				auto t_unit = unfold::source(std::move(source));
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


#include "compile/compile.hxx"
#include <iostream>
#include "ltn/InstructionSet.hxx"
#include "print/print.hxx"

namespace ltn::c {
	namespace {
		void startup_code(std::ostream & out, FxTable & fx_table) {
			// Jump to main()
			if(const auto fxmain = fx_table.resolve("main", {}, 0)) {
				const auto code = std::to_array<ltn::inst::Instruction>({
					ltn::inst::Call{fxmain->id},
					ltn::inst::Exit{}
				});
				out << print(code);
			}
			// Jump to main()
			else if(const auto fxmain = fx_table.resolve("main", {}, 1)) {
				const auto code = std::to_array<ltn::inst::Instruction>({
					ltn::inst::Call{fxmain->id},
					ltn::inst::Exit{}
				});
				out << print(code);
			}
			else {
				throw CompilerError {"main() is undefined", {}};
			}
		}


		void op_chain_code(std::ostream & out) {
			out << 
				":_lambda_chain\n"
				"parameters 3\n"
				"read_1\n"
				"read_2\n"
				"read_0\n"
				"newarr 1\n"
				"invoke\n"
				"newarr 1\n"
				"invoke\n"
				"return\n"
				"\n";

			out << 
				":_op_chain\n"
				"parameters 2\n"
				"newfx _lambda_chain 1\n"
				"read_0\n"
				"capture\n"
				"read_1\n"
				"capture\n"
				"return\n"
				"\n";
		}


		void op_pipe_code(std::ostream & out) {
			static const auto code = std::to_array<ltn::inst::Instruction>({
				ltn::inst::Label{"_op_pipe"},
				ltn::inst::Newarr{1},
				ltn::inst::Invoke{},
				ltn::inst::Return{},
			});

			out << print(code);
		}
	}

	// compiles source
	std::string compile(
		const ast::Program & program,
		const Config & config,
		Reporter & reporter) {
		
		std::stringstream out;
		GlobalTable global_table;
		FxTable fx_table;
		MemberTable member_table;
		CompilerInfo info {
			config,
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
			startup_code(out, fx_table);
			op_chain_code(out);
			op_pipe_code(out);
		}
		catch(const CompilerError & error) {
			reporter.push(error);
		}

		for(const auto & function : program.functions) {
			try {
				out << print(compile_functional(*function, info).get()); 
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}

		return out.str();
	}
}