#include "compile.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr analyze_write(
			const ast::Assignable & expr,
			CompilerInfo & info,
			Scope & scope) {
			
			if(auto e = as<ast::Var>(expr)) {
				const auto var = scope.resolve(e->name, expr.location);
				if(!var) throw CompilerError {
					"Undefined variable" + e->name,
					e->location
				};
				return std::make_unique<sst::Var>(var->address, var->type);
			}
			
			if(auto e = as<ast::Index>(expr)) {
				auto container = analyze_expression(*e->expression, info, scope);
				auto index = analyze_expression(*e->index, info, scope);
				return std::make_unique<sst::Index>(
					std::move(container),
					std::move(index),
					type::deduce_index(container->type, index->type)
				);
			}
			
			if(auto e = as<ast::Member>(expr)) {
				const auto id = info.member_table.get_id(e->name);
				return std::make_unique<sst::Member>(
					type::Any{}, 
					id
				);
			}
			
			if(auto global = as<ast::GlobalVar>(expr)) {
				auto glob = info.global_table.resolve(
					global->name, scope.get_namespace(), global->namespaze 
				);
				return std::make_unique<sst::GlobalVar>(
					instantiate_type(glob->type, scope),
					glob->id);
			}

			throw std::runtime_error{"Unknown assingable type"};
		}
	}



	sst::stmt_ptr analyze_stmt(
		const ast::Assign & expr,
		CompilerInfo & info,
		Scope & scope) {
		guard_const(expr, scope);
		auto l = analyze_write(static_cast<ast::Assignable&>(*expr.l), info, scope);
		auto r = analyze_expression(*expr.r, info, scope);

		return std::make_unique<sst::Assign>(0, false, std::move(l), std::move(r));
	}



	namespace {
		sst::expr_ptr analyze_new_variable_right(
			const ast::NewVar & new_var,
			CompilerInfo & info,
			Scope & scope) {
			
			if(new_var.expression) {
				return analyze_expression(*new_var.expression, info, scope);
			}
			else {
				return std::make_unique<sst::Null>(type::Null{});
			}
		}


		Variable insert_new_var(
			const ast::NewVar & new_var,
			Scope & scope,
			const type::Type & r_type) {

			auto imcomplete = std::get_if<type::IncompleteType>(&new_var.type);
			if(imcomplete) {
				const auto type = instantiate_type(*imcomplete, scope);
				return scope.insert(new_var.name, new_var.location, type);		
			}
			return scope.insert(new_var.name, new_var.location, r_type);		
		}
	}



	std::unique_ptr<sst::NewVar> analyze_stmt(
		const ast::NewVar & new_var,
		CompilerInfo & info,
		Scope & scope) {
		
		auto r = analyze_new_variable_right(new_var, info, scope);		
		const auto var = insert_new_var(new_var, scope, r->type);		
		return std::make_unique<sst::NewVar>(0, true, var.address, std::move(r), var.type);
	}
}