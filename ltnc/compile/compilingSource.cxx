#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		auto makeFxId(CompilerInfo & info, const std::string_view name) {
			std::stringstream ss;
			ss << "FX" << info.jumpMarkCounter++ << "_" << name;
			return ss.str();
		}
	}

	std::string source(const ast::Source & source, CompilerInfo & info) {
		std::stringstream ss;
		
		for(const auto & fx : source.functions) {
			info.fxTable.insert({
				fx->name,
				fx->parameters.size(),
				makeFxId(info, fx->name)});
		}

		for(const auto & function : source.functions) {
			ss << compile::function(*function, info); 
		}
		
		return ss.str();
	}
}