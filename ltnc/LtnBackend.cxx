#include "LtnBackend.hxx"
#include "compile/compile.hxx"
#include <iostream>

namespace ltn::c::compile {
	namespace {
		void startup_code(std::ostream & out, FxTable & fx_table) {
			// Jump to main()
			if(const auto fxmain = fx_table.resolve("main", {}, 0)) {
				out
					<< compile::inst::call(fxmain->id) 
					<< compile::inst::exlt
					<< "\n";
			}
			// Jump to main()
			else if(const auto fxmain = fx_table.resolve("main", {}, 1)) {
				out
					<< compile::inst::call(fxmain->id) 
					<< compile::inst::exlt
					<< "\n";
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
			out << 
				":_op_pipe\n"
				"newarr 1\n"
				"invoke\n"
				"return\n"
				"\n";
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