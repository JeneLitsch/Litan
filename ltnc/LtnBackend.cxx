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
			else {
				throw CompilerError {"main() is undefined", {}};
			}
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