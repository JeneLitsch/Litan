#include "compile.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	namespace {

		// compile assignable variable
		InstructionBuffer compile_read_ref(const sst::Assignable & expr) {
			
			if(auto e = as<sst::Var>(expr)) {
				return {};
			}
			
			if(auto index = as<sst::Index>(expr)) {
				InstructionBuffer buf;
				buf << compile_expression(*index->expression);
				return buf;
			}
			
			if(auto e = as<sst::Member>(expr)) {
				InstructionBuffer buf;
				buf << compile_expression(*e->expr);
				return InstructionBuffer{ buf };
			}

			if(auto g = as<sst::GlobalVar>(expr)) {
				return {};
			}
			
			throw std::runtime_error{"Unknow assingable type"};
		}



		InstructionBuffer compile_write(const sst::Assignable & expr) {
			
			if(auto e = as<sst::Var>(expr)) {
				InstructionBuffer buf;
				buf << inst::write_x(e->addr);
				return buf;
			}
			
			if(auto e = as<sst::Index>(expr)) {
				const auto idx = compile_expression(*e->index);
				InstructionBuffer buf;
				buf << idx;
				buf << inst::at_write();
				return buf;
			}
			
			if(auto e = as<sst::Member>(expr)) {
				InstructionBuffer buf;
				buf << inst::member_write(e->addr);
				return buf;
			}
			
			if(auto global = as<sst::GlobalVar>(expr)) {
				return compile_write_global(*global);
			}

			throw std::runtime_error{"Unknown assingable type"};
		}
	}




	InstructionBuffer compile_stmt(const sst::Assign & expr) {
		const auto l_prepare = compile_read_ref(static_cast<sst::Assignable&>(*expr.l));
		const auto l_write = compile_write(static_cast<sst::Assignable&>(*expr.l));
		const auto r = compile_expression(*expr.r);

		InstructionBuffer buf;
		buf << r;
		buf << l_prepare;
		buf << l_write;
		return buf;
	}



	namespace {
		InstructionBuffer compile_new_variable_right(const sst::NewVar & new_var) {
			
			if(new_var.expression) {
				return compile_expression(*new_var.expression);
			}
			else {
				InstructionBuffer buf;
				buf << inst::null();
				return buf;
			}
		}
	}



	InstructionBuffer compile_stmt(const sst::NewVar & new_var) {
		InstructionBuffer buf;
		buf <<  compile_new_variable_right(new_var);
		buf << inst::write_x(new_var.addr);
		return buf;
	}
}