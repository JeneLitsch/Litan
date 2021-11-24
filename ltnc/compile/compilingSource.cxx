#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		auto makeFxId(CompilerInfo & info, const std::string_view name, std::size_t params) {
			std::stringstream ss;
			ss << "FX" << info.jumpMarkCounter++ << "_" << name << "_" << params;
			return ss.str();
		}
	}

	std::string source(const ast::Source & source, CompilerInfo & info) {
		std::stringstream ss;
		
		for(const auto & fx : source.functions) {
			info.fxTable.insert({
				fx->name,
				fx->parameters.size(),
				makeFxId(info, fx->name, fx->parameters.size())});
		}

		for(const auto & function : source.functions) {
			ss << compile::functional(*function, info); 
		}
		
		return ss.str();
	}
}