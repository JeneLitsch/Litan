#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	ExprResult compile_invokation(
		const ast::Invokation & invoke,
		CompilerInfo & info,
		Scope & scope) {

		InstructionBuffer buf;

		auto fx_ptr = compile_expression(*invoke.function_ptr, info, scope);

		buf << fx_ptr.code;

		for(const auto & param : invoke.parameters) {
			buf << compile_expression(*param, info, scope).code;
		}

		buf << inst::newarr(invoke.parameters.size());
		buf << inst::invoke();
		
		return {
			.code = buf,
			.deduced_type = type::deduce_invokation(fx_ptr.deduced_type),
		};
	}
}