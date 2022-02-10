#include "LtnBackend.hxx"
#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		auto makeFxId(
			CompilerInfo & info,
			const ast::Functional & fx) {
			std::stringstream ss;
			ss << "FX" << info.jumpMarkCounter++;
			for(const auto & sns : fx.nameSpace) {
				ss << "_" << sns;
			}
			ss << "_" << fx.name << "_" << fx.parameters.size();
			return ss.str();
		}

		void initCode(std::ostream & out, FxTable & fxTable) {
			// Jump to main()
			if(const auto fxmain = fxTable.resolve("main", {}, 0)) {
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
		const std::vector<std::unique_ptr<ast::Functional>> & functions,
		Reporter & reporter) {
		
		compile::CompilerInfo info {
			config,
			this->fxTable,
			this->memberTable,
			this->jumpMarkCounter,
			reporter};
		
		for(const auto & fx : functions) {
			info.fxTable.insert({
				fx->name,
				fx->nameSpace,
				fx->parameters.size(),
				makeFxId(info, *fx)});
		}

		try {
			initCode(out, fxTable);
		}
		catch(const CompilerError & error) {
			reporter.push(error);
		}

		for(const auto & function : functions) {
			try {
				out << compile::functional(*function, info); 
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}
	}
}