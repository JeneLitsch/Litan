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



	namespace {
		InstructionBuffer compile_binding(const sst::Binding & binding);
		
		
		
		InstructionBuffer compile_bind(const sst::VarBinding & binding) {
			InstructionBuffer buf;
			buf << inst::write_x(binding.addr);
			return buf;
		}
		


		InstructionBuffer compile_bind(const sst::GroupBinding & binding) {
			InstructionBuffer buf;
			buf << inst::unpack(std::size(binding.sub_bindings));
			for(const auto & sub : binding.sub_bindings) {
				buf << compile_binding(*sub);
			}
			return buf;
		}


		
		InstructionBuffer compile_binding(const sst::Binding & binding) {
			return sst::visit_binding(binding, [&] (const auto & b) {
				return compile_bind(b);
			});
		}
	}



	InstructionBuffer compile_stmt(const sst::NewVar & new_var) {
		InstructionBuffer buf;
		buf << compile_expression(*new_var.expression);
		buf << compile_binding(*new_var.binding);
		return buf;
	}
}