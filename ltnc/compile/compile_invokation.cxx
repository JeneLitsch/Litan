#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	ExprCode invokation(
		const ast::Invokation & invoke,
		CompilerInfo & info,
		Scope & scope) {

		std::ostringstream oss;

		oss << expression(*invoke.function_ptr, info, scope).code;

		for(const auto & param : invoke.parameters) {
			oss << expression(*param, info, scope).code;
		}

		oss << inst::newarr(invoke.parameters.size());
		oss << inst::invoke;
		
		return ExprCode{ oss.str() };
	}
}