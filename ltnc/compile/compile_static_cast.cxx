#include "compile.hxx"
#include "ltnc/compile/static_cast.hxx"

namespace ltn::c {
	ExprResult compile_static_cast(
		const ast::StaticCast & cast,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto inner = compile_expression(*cast.expr, info, scope);
		const auto outer = cast_static(inner.deduced_type, cast.type, cast.location);

		InstructionBuffer buf;
		buf << inner.code;
		buf << outer; 

		return ExprResult {
			.code = buf,
			.deduced_type = cast.type,
		};
	}
}