#include "compile.hxx"
#include <iostream>

#include "ltnc/sst/bind/Group.hxx"
#include "ltnc/sst/bind/NewVar.hxx"
#include "ltnc/sst/bind/Discard.hxx"
#include "ltnc/sst/bind/Global.hxx"
#include "ltnc/sst/bind/Member.hxx"
#include "ltnc/sst/bind/Local.hxx"
#include "ltnc/sst/bind/Index.hxx"

#include "ltnc/sst/stmt/Assign.hxx"

namespace ltn::c {
	InstructionBuffer compile_binding(const sst::bind::Binding & binding);
	namespace {
		
		
		
		InstructionBuffer compile_bind(const sst::bind::NewVar & binding) {
			InstructionBuffer buf;
			buf << inst::store_x(binding.address);
			return buf;
		}
		


		InstructionBuffer compile_bind(const sst::bind::Group & binding) {
			InstructionBuffer buf;
			const auto size = std::size(binding.sub_bindings);
			buf << inst::unpack(static_cast<std::uint8_t>(size));
			for(const auto & sub : binding.sub_bindings) {
				buf << compile_binding(*sub);
			}
			return buf;
		}



		InstructionBuffer compile_bind(const sst::bind::Discard &) {
			InstructionBuffer buf;
			buf << inst::scrap();
			return buf;
		}



		InstructionBuffer compile_bind(const sst::bind::Global & binding) {
			InstructionBuffer buf;
			buf << inst::global_write(binding.address);
			return buf;
		}



		InstructionBuffer compile_bind(const sst::bind::Member & binding) {
			InstructionBuffer buf;
			buf << compile_expression(*binding.object);
			buf << inst::member_write(binding.address);
			return buf;
		}
		
		
		
		InstructionBuffer compile_bind(const sst::bind::Local & binding) {
			InstructionBuffer buf;
			buf << inst::store_x(binding.address);
			return buf;
		}
		
		
		
		InstructionBuffer compile_bind(const sst::bind::Index & binding) {
			InstructionBuffer buf;
			buf << compile_expression(*binding.range);
			buf << compile_expression(*binding.index);
			buf << inst::at_write();
			return buf;
		}
	}



	InstructionBuffer compile_binding(const sst::bind::Binding & binding) {
		auto fx = [&] (const auto & b) { return compile_bind(b); };
		return sst::bind::visit(binding, fx);
	}



	InstructionBuffer compile_stmt(const sst::stmt::Assign & new_var) {
		InstructionBuffer buf;
		buf << compile_expression(*new_var.expr);
		buf << compile_binding(*new_var.binding);
		return buf;
	}
}