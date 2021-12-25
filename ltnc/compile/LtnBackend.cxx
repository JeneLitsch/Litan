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
		
		std::stringstream buffer;
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

		for(const auto & function : functions) {
			buffer << compile::functional(*function, info); 
		}
		
		// Jump to main()
		if(const auto fxmain = this->fxTable.resolve("main", {}, 0)) {
			out	<< compile::inst::call(fxmain->id) 
				<< compile::inst::exlt
				<< "\n";
			out << buffer.rdbuf();
		}
		else {
			throw CompilerError {"main() is undefined", 0};
		}
	}
}