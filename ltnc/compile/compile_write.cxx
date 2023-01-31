#include "compile.hxx"
#include "ltnc/type/traits.hxx"
#include <iostream>

namespace ltn::c {
	namespace {
		InstructionBuffer compile_binding(const sst::Binding & binding);
		
		
		
		InstructionBuffer compile_bind(const sst::NewVarBinding & binding) {
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



		InstructionBuffer compile_bind(const sst::NoBinding & binding) {
			InstructionBuffer buf;
			buf << inst::scrap();
			return buf;
		}



		InstructionBuffer compile_bind(const sst::GlobalBinding & binding) {
			InstructionBuffer buf;
			buf << inst::global_write(binding.addr);
			return buf;
		}



		InstructionBuffer compile_bind(const sst::MemberBinding & binding) {
			InstructionBuffer buf;
			buf << compile_expression(*binding.object);
			buf << inst::member_write(binding.addr);
			return buf;
		}
		
		
		
		InstructionBuffer compile_bind(const sst::LocalBinding & binding) {
			InstructionBuffer buf;
			buf << inst::write_x(binding.addr);
			return buf;
		}
		
		
		
		InstructionBuffer compile_bind(const sst::IndexBinding & binding) {
			InstructionBuffer buf;
			buf << compile_expression(*binding.range);
			buf << compile_expression(*binding.index);
			buf << inst::at_write();
			return buf;
		}


		
		InstructionBuffer compile_binding(const sst::Binding & binding) {
			return sst::visit_binding(binding, [&] (const auto & b) {
				return compile_bind(b);
			});
		}
	}



	InstructionBuffer compile_stmt(const sst::Assign & new_var) {
		InstructionBuffer buf;
		buf << compile_expression(*new_var.expression);
		buf << compile_binding(*new_var.binding);
		return buf;
	}
}