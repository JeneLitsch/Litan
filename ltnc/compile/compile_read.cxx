#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	InstructionBuffer compile_expr(const sst::Var & expr) {
		InstructionBuffer buf;
		buf << inst::read_x(expr.addr);
		return buf;
	}

	
	InstructionBuffer compile_expr(const sst::Member & access) {
		InstructionBuffer buf;
		buf << compile_expression(*access.expr);
		buf << inst::member_read(access.addr);
		return buf;
	}
}