#include "compile.hxx"
#include "ltnc/type/traits.hxx"
#include <iostream>

namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::AssignLocal & stmt) {
		const auto r = compile_expression(*stmt.r);
		InstructionBuffer buf;
		buf << r;
		buf << inst::write_x(stmt.addr);
		return buf;
	}



	InstructionBuffer compile_stmt(const sst::AssignIndex & stmt) {
		InstructionBuffer buf;
		buf << compile_expression(*stmt.r);
		buf << compile_expression(*stmt.range);
		buf << compile_expression(*stmt.index);
		buf << inst::at_write();
		return buf;
	}



	InstructionBuffer compile_stmt(const sst::AssignMember & stmt) {
		InstructionBuffer buf;
		buf << compile_expression(*stmt.r);
		buf << compile_expression(*stmt.object);
		buf << inst::member_write(stmt.addr);
		return buf;
	}



	InstructionBuffer compile_stmt(const sst::AssignGlobal & stmt) {
		const auto r = compile_expression(*stmt.r);
		InstructionBuffer buf;
		buf << r;
		buf << inst::global_write(stmt.addr);
		return buf;
	}



	InstructionBuffer compile_stmt(const sst::NewVar & new_var) {
		InstructionBuffer buf;
		buf << compile_expression(*new_var.expression);
		buf << inst::write_x(new_var.addr);
		return buf;
	}


	InstructionBuffer compile_stmt(const sst::StructuredBinding & new_vars) {
		InstructionBuffer buf;
		buf << compile_expression(*new_vars.expression);
		buf << inst::unpack(std::size(new_vars.addrs));
		for(const auto addr : new_vars.addrs) {
			buf << inst::write_x(addr);
		}
		return buf;
	}
}