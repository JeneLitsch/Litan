#include "compiling.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include "Instructions.hxx"
#include "ltnc/type/Primitives.hxx"
#include "utils.hxx"
namespace ltn::c::compile {

	std::string function(const ast::Function & fx, CompilerInfo & info) {
		const auto & fxSig = info.fxTable.find(fx.name, toTypes(fx.parameters));
		std::stringstream ss;
		ss << inst::comment("Function " + fx.name);
		ss << inst::jumpmark(fxSig->id);
		if(type::isVoid(fx.returnType)) {
			ss << inst::r3turn;
		}
		else {
			ss << inst::error;
		}
		return ss.str();
	}
}