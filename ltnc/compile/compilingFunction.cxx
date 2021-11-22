#include "compiling.hxx"

namespace ltn::c::compile {

	std::string function(const ast::Function & fx, CompilerInfo & info) {
		Scope scope;
		std::stringstream ss;
		const auto & fxSig = info.fxTable.find(fx.name, fx.parameters.size());
		ss << inst::jumpmark(fxSig->id);
		for(const auto & param : fx.parameters) {
			const auto addr = scope.insert(param, fx.debugInfo.line);
			ss << inst::makevar;
			ss << inst::addr(addr);
			ss << inst::write;
		}
		if(fx.body) {
			ss << compile::statement(*fx.body, info, scope).code;
		}
		ss << inst::null;
		ss << inst::reTurn;
		ss << "\n";
		return ss.str();
	}
}