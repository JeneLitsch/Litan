#include "compile.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	namespace {

		// compile assignable variable
		ExprResult compile_read_ref(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(auto var = as<ast::Var>(expr)) {
				if(!var->namespaze.empty()) throw CompilerError{
					"Local variable must not have a namespace", var->location
				};
				const auto & local = scope.resolve(var->name, var->location);
				return {
					.code = {},
					.deduced_type = local.type,
				};
			}
			
			if(auto index = as<ast::Index>(expr)) {
				const auto arr = compile_expression(*index->expression, info, scope);
				const auto idx = compile_expression(*index->index, info, scope);
				InstructionBuffer buf;
				buf << arr.code;
				return ExprResult{ 
					.code = buf,
					.deduced_type = type::deduce_index(arr.deduced_type, idx.deduced_type)
				};
			}
			
			if(auto e = as<ast::Member>(expr)) {
				InstructionBuffer buf;
				buf << compile_expression(*e->expr, info, scope).code;
				return ExprResult{ buf };
			}

			if(auto g = as<ast::GlobalVar>(expr)) {
				auto global = info.global_table.resolve(g->name, scope.get_namespace(), g->namespaze);
				if(!global) throw CompilerError{""};
				return {
					.code = {},
					.deduced_type = global->type,
				};
			}
			
			throw std::runtime_error{"Unknow assingable type"};
		}



		InstructionBuffer compile_write(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(auto e = as<ast::Var>(expr)) {
				const auto var = scope.resolve(e->name, expr.location);
				InstructionBuffer buf;
				buf << inst::write_x(var.address);
				return buf;
			}
			
			if(auto e = as<ast::Index>(expr)) {
				const auto idx = compile_expression(*e->index, info, scope);
				InstructionBuffer buf;
				buf << idx.code;
				buf << inst::at_write();
				return buf;
			}
			
			if(auto e = as<ast::Member>(expr)) {
				InstructionBuffer buf;
				const auto id = info.member_table.get_id(e->name);
				buf << inst::member_write(id);
				return buf;
			}
			
			if(auto global = as<ast::GlobalVar>(expr)) {
				return compile_write_static(*global, info, scope).code;
			}

			throw std::runtime_error{"Unknown assingable type"};
		}
	}



	StmtResult compile_assign(
		const ast::Assign & expr,
		CompilerInfo & info,
		Scope & scope) {
		guard_const(expr, scope);
		const auto l_prepare = compile_read_ref(*expr.l, info, scope);
		const auto l_write = compile_write(*expr.l, info, scope);
		const auto r = compile_expression(*expr.r, info, scope);

		InstructionBuffer buf;
		buf << r.code;
		buf << l_prepare.code;
		buf << conversion_on_assign(
			r.deduced_type,
			l_prepare.deduced_type,
			expr.location
		);
		buf << l_write;
		return StmtResult{ 
			.code = buf,
			.var_count = 0,
			.direct_allocation = false,
		};
	}



	namespace {
		ExprResult compile_new_variable_right(
			const ast::NewVar & new_var,
			CompilerInfo & info,
			Scope & scope) {
			
			if(new_var.expression) {
				return compile_expression(*new_var.expression, info, scope);
			}
			else {
				InstructionBuffer buf;
				buf << inst::null();
				return ExprResult {
					.code = buf,
					.deduced_type = type::Null{}, 
				};
			}
		}
	}



	StmtResult compile_new_variable(const ast::NewVar & new_var, CompilerInfo & info, Scope & scope) {
		const auto var = scope.insert(new_var.name, new_var.location, new_var.type);
		const auto r = compile_new_variable_right(new_var, info, scope);
		
		InstructionBuffer buf;
		buf << r.code;
		buf << conversion_on_assign(
			r.deduced_type,
			new_var.type,
			new_var.location
		);
		buf << inst::write_x(var.address);
		return { 
			.code = buf,
			.var_count = 0,
			.direct_allocation = true,
		};
	}
}