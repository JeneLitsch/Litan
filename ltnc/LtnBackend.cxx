#include "LtnBackend.hxx"
#include "compile/compile.hxx"
#include <iostream>
#include "ltn/InstructionSet.hxx"
#include "print/print.hxx"

namespace ltn::c::compile {
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
	void LtnBackend::compile(
		std::ostream & out,
		const Config & config,
		const ast::Program & program,
		Reporter & reporter) {
		
		GlobalTable global_table;
		FxTable fx_table;
		MemberTable member_table;
		
		compile::CompilerInfo info {
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
				out << compile::functional(*function, info); 
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}
	}
}