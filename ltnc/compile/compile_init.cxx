#include "compile.hxx"
#include "ltnc/sst/expr/Map.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::InitStruct & init) {
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



	InstructionBuffer compile_expr(const sst::Map & map) {
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