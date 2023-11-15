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
	namespace {
		InstructionBuffer compile_binding(const sst::bind::Binding & binding);
		
		
		
		InstructionBuffer compile_bind(const sst::bind::NewVar & binding) {
			InstructionBuffer buf;
			buf << inst::write_x(binding.address);
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
			buf << inst::write_x(binding.address);
			return buf;
		}
		
		
		
		InstructionBuffer compile_bind(const sst::bind::Index & binding) {
			InstructionBuffer buf;
			buf << compile_expression(*binding.range);
			buf << compile_expression(*binding.index);
			buf << inst::at_write();
			return buf;
		}


		
		InstructionBuffer compile_binding(const sst::bind::Binding & binding) {
			auto fx = [&] (const auto & b) {
				return compile_bind(b);
			};
			using Callable = std::decay_t<decltype(fx)>;
			using Ret = std::invoke_result_t<Callable, sst::bind::Discard>;
			using Base = FunctionVisitor<sst::bind::BindVisitor, Callable, Ret>;
			
			struct Visitor : public Base {
				Visitor(Callable fx) : Base {fx} {} 
				
				virtual void visit(const sst::bind::Group & x)   const override { this->run(x); };
				virtual void visit(const sst::bind::NewVar & x)  const override { this->run(x); };
				virtual void visit(const sst::bind::Discard & x) const override { this->run(x); };
				virtual void visit(const sst::bind::Global & x)  const override { this->run(x); };
				virtual void visit(const sst::bind::Member & x)  const override { this->run(x); };
				virtual void visit(const sst::bind::Local & x)   const override { this->run(x); };
				virtual void visit(const sst::bind::Index & x)   const override { this->run(x); };
			};

			return Visitor{fx}(binding);
		}
	}



	InstructionBuffer compile_stmt(const sst::stmt::Assign & new_var) {
		InstructionBuffer buf;
		buf << compile_expression(*new_var.expr);
		buf << compile_binding(*new_var.binding);
		return buf;
	}
}