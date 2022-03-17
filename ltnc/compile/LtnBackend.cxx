#include "LtnBackend.hxx"
#include "compiling.hxx"
#include <iostream>

namespace ltn::c::compile {
	namespace {
		auto make_fxid(
			CompilerInfo & info,
			const ast::Functional & fx) {
			std::stringstream ss;
			ss << "FX" << info.jump_mark_counter++;
			for(const auto & sns : fx.namespaze) {
				ss << "_" << sns;
			}
			ss << "_" << fx.name << "_" << fx.parameters.size();
			return ss.str();
		}

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
		
		EnumTable enum_table;
		FxTable fx_table;
		MemberTable member_table;
		std::size_t jump_mark_counter = 0;
		
		compile::CompilerInfo info {
			config,
			fx_table,
			enum_table,
			member_table,
			jump_mark_counter,
			reporter};
		
		for(const auto & fx : program.functions) {
			info.fx_table.insert({
				fx->name,
				fx->namespaze,
				fx->parameters.size(),
				make_fxid(info, *fx)});
		}

		for(const auto & e : program.enums) {
			info.enum_table.insert({
				e->name,
				e->namespaze,
				e.get()});
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