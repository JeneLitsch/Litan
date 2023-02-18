#include "compile.hxx"


namespace ltn::c {
	// compiles any expr
	InstructionBuffer compile_expression(const sst::Expression & expr) {
		return sst::visit_expression(expr, [&](const auto & e) {
			return compile_expr(e);
		});
	}
}