#include "compile.hxx"
#include <string_view>
#include "ltnc/sst/expr/Member.hxx"
#include "ltnc/sst/expr/Var.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::expr::Var & expr) {
		InstructionBuffer buf;
		buf << inst::load_x(expr.address);
		return buf;
	}

	
	InstructionBuffer compile_expr(const sst::expr::Member & access) {
		InstructionBuffer buf;
		buf << compile_expression(*access.expr);
		buf << inst::member_read(access.address);
		return buf;
	}
}