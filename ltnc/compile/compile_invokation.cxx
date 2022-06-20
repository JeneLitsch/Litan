#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	ExprCode invokation(
		const ast::Invokation & invoke,
		CompilerInfo & info,
		Scope & scope) {

		InstructionBuffer buf;

		buf << expression(*invoke.function_ptr, info, scope).code;

		for(const auto & param : invoke.parameters) {
			buf << expression(*param, info, scope).code;
		}

		buf << ltn::inst::Newarr{invoke.parameters.size()};
		buf << ltn::inst::Invoke{};
		
		return { buf };
	}
}