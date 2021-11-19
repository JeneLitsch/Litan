#include "compiling.hxx"

namespace ltn::c::compile {

	std::string_view tail(const type::Type & returnType) {
		if(type::isVoid(returnType)) {
			return inst::r3turn;
		}
		return inst::error;
	} 

	std::string function(const ast::Function & fx, CompilerInfo & info) {
		const auto & fxSig = info.fxTable.find(fx.name, toTypes(fx.parameters));
		std::stringstream ss;
		ss << inst::jumpmark(fxSig->id);
		if(fx.body) {
			ss << compile::statement(*fx.body, info).code;
		}
		ss << tail(fx.returnType);
		return ss.str();
	}
}