#include "compile.hxx"
#include "ltnc/compile/cast_static.hxx"
#include "ltnc/compile/cast_dynamic.hxx"

namespace ltn::c {
	namespace {
		ExprResult compile_copy(
			const auto & actual_copy,
			const auto & deduce_type,
			const auto & copy,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto inner = compile_expression(*copy.expr, info, scope);
			const auto outer = actual_copy(inner.deduced_type, copy.type, copy.location);

			InstructionBuffer buf;
			buf << inner.code;
			buf << outer; 

			return ExprResult {
				.code = buf,
				.deduced_type = deduce_type(copy.type),
			};
		}
	}


	ExprResult compile_static_copy(
		const ast::StaticCopy & copy,
		CompilerInfo & info,
		Scope & scope) {

		return compile_copy(cast_static, type::deduce_cast_static, copy, info, scope);
	}



	ExprResult compile_dynamic_copy(
		const ast::DynamicCopy & copy,
		CompilerInfo & info,
		Scope & scope) {

		return compile_copy(cast_dynamic, type::deduce_cast_dynamic, copy, info, scope);
	}
}