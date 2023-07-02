#include "compile.hxx"
#include "build_in.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::RunBuildIn & expr) {
		return { resolve_build_in(expr.key) };
	}


	// compiles any expr
	InstructionBuffer compile_expression(const sst::Expression & expr) {
		return sst::visit_expression(expr, [&](const auto & e) {
			return compile_expr(e);
		});
	}
}