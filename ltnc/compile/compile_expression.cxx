#include "compile.hxx"
#include "build_in.hxx"
#include "ltnc/sst/expr/BuildIn.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::expr::BuildIn & expr) {
		return { resolve_build_in(expr.key) };
	}


	// compiles any expr
	InstructionBuffer compile_expression(const sst::expr::Expression & expr) {
		auto fx = [&](const auto & e) { return compile_expr(e); };
		return sst::expr::visit<InstructionBuffer>(expr, fx);
	}
}