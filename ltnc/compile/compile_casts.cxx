#include "compile.hxx"
#include "ltnc/compile/cast_static.hxx"
#include "ltnc/compile/cast_dynamic.hxx"

namespace ltn::c {
	namespace {
		ExprResult compile_cast(
			const auto & actual_cast,
			const auto & cast,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto inner = compile_expression(*cast.expr, info, scope);
			const auto outer = actual_cast(inner.deduced_type, cast.type, cast.location);

			InstructionBuffer buf;
			buf << inner.code;
			buf << outer; 

			return ExprResult {
				.code = buf,
				.deduced_type = cast.type,
			};
		}
	}


	ExprResult compile_static_cast(
		const ast::StaticCast & cast,
		CompilerInfo & info,
		Scope & scope) {

		return compile_cast(cast_static, cast, info, scope);
	}



	ExprResult compile_dynamic_cast(
		const ast::DynamicCast & cast,
		CompilerInfo & info,
		Scope & scope) {

		return compile_cast(cast_dynamic, cast, info, scope);
	}
}