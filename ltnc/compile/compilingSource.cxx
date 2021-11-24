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
	std::string source(const ast::Source & source, CompilerInfo & info) {
		std::stringstream ss;
		
		for(const auto & fx : source.functions) {
			info.fxTable.insert({
				fx->name,
				fx->nameSpace,
				fx->parameters.size(),
				makeFxId(info, *fx)});
		}

		for(const auto & function : source.functions) {
			ss << compile::functional(*function, info); 
		}
		
		return ss.str();
	}
}