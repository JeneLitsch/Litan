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
	}

	// compiles source
	void LtnBackend::compile(
		std::ostream & out,
		const Config & config,
		const std::vector<std::unique_ptr<ast::Functional>> & functions) {
		
		compile::CompilerInfo info {
			config,
			this->fxTable,
			this->memberTable,
			this->jumpMarkCounter};
		
		for(const auto & fx : functions) {
			info.fxTable.insert({
				fx->name,
				fx->nameSpace,
				fx->parameters.size(),
				makeFxId(info, *fx)});
		}

		// Jump to main()
		if(const auto fxmain = this->fxTable.resolve("main", {}, 0)) {
			out
				<< compile::inst::call(fxmain->id) 
				<< compile::inst::exlt
				<< "\n";
		}
		else {
			throw CompilerError {"main() is undefined", 0};
		}

		for(const auto & function : functions) {
			out << compile::functional(*function, info); 
		}
	}
}