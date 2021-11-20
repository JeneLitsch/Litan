#include "compiling.hxx"

namespace ltn::c::compile {

	std::string function(const ast::Function & fx, CompilerInfo & info) {
		Scope scope;
		const auto & fxSig = info.fxTable.find(fx.name, fx.parameters.size());
		std::stringstream ss;
		ss << inst::jumpmark(fxSig->id);
		if(fx.body) {
			ss << compile::statement(*fx.body, info, scope).code;
		}
		ss << inst::null;
		ss << inst::reTurn;
		ss << "\n";
		return ss.str();
	}
}