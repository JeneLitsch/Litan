#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		auto makeFxId(CompilerInfo & info) {
			std::stringstream ss;
			ss << "FX" << info.jumpMarkCounter++;
			return ss.str();
		}
	}

	std::string source(const ast::Source & source, CompilerInfo & info) {
		std::stringstream ss;
		
		for(const auto & fx : source.functions) {
			info.fxTable.insert({
				fx->name,
				fx->parameters.size(),
				makeFxId(info)});
		}

		for(const auto & function : source.functions) {
			ss << compile::function(*function, info); 
		}
		
		return ss.str();
	}
}