#include "compile.hxx"
#include "litan_compiler/sst/expr/Map.hxx"
#include "litan_compiler/sst/expr/Struct.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::expr::Struct & init) {
		InstructionBuffer buf;
		buf << inst::newstruct();
		for(const auto & [member, expr] : init.members) {
			buf << inst::duplicate();
			buf << compile_expression(*expr);
			buf << inst::swap();
			buf << inst::member_write(member);
		}
		return buf;
	}



	InstructionBuffer compile_expr(const sst::expr::Map & map) {
		InstructionBuffer buf;
		buf << inst::newmap();
		for(auto & [key, val] : map.pairs) {
			buf << inst::duplicate();
			buf << compile_expression(*val);
			buf << inst::swap();
			buf << compile_expression(*key);
			buf << inst::at_write();
		}
		return buf;
	}
}