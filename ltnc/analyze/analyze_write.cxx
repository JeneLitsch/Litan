#include "analyze.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr analyze_write(
			const ast::Assignable & expr,
			Context & context,
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
				auto container = analyze_expression(*e->expression, context, scope);
				auto index = analyze_expression(*e->index, context, scope);
				return std::make_unique<sst::Index>(
					std::move(container),
					std::move(index),
					type::deduce_index(container->type, index->type)
				);
			}
			
			if(auto e = as<ast::Member>(expr)) {
				const auto id = context.member_table.get_id(e->name);
				auto expr = analyze_expression(*e->expr, context, scope);
				return std::make_unique<sst::Member>(
					type::Any{},
					std::move(expr), 
					id
				);
			}
			
			if(auto global = as<ast::GlobalVar>(expr)) {
				auto glob = context.global_table.resolve(
					global->name,
					scope.get_namespace(),
					global->namespaze 
				);
				if(!glob) {
					throw CompilerError {
						"Cannot write to undegined global " + global->name,
						global->location
					};
				}
				return std::make_unique<sst::GlobalVar>(
					glob->type,
					glob->id);
			}

		}
	}


	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw CompilerError{
				"Cannot modify or reassign variable in const function",
				node.location};
		}
	}



	sst::stmt_ptr analyze_stmt(
		const ast::Assign & expr,
		Context & context,
		Scope & scope) {
		guard_const(expr, scope);
		auto l = analyze_write(static_cast<ast::Assignable&>(*expr.l), context, scope);
		auto r = conversion_on_assign(analyze_expression(*expr.r, context, scope), l->type, expr.location);
		if(auto * l_local = dynamic_cast<sst::Var *>(l.get())) {
			return std::make_unique<sst::AssignLocal>(
				0, false,
				l_local->addr,
				std::move(r)
			);
		}
		if(auto * l_index = dynamic_cast<sst::Index *>(l.get())) {
			return std::make_unique<sst::AssignIndex>(
				0, false,
				std::move(l_index->expression),
				std::move(l_index->index),
				std::move(r)
			);
		}
		if(auto * l_member = dynamic_cast<sst::Member *>(l.get())) {
			return std::make_unique<sst::AssignMember>(
				0, false,
				std::move(l_member->expr),
				l_member->addr,
				std::move(r)
			);
		}
		if(auto * l_global = dynamic_cast<sst::GlobalVar *>(l.get())) {
			return std::make_unique<sst::AssignGlobal>(
				0, false,
				l_global->addr,
				std::move(r)
			);
		}
		throw CompilerError {
			"Left side is not assignable",
			expr.location
		};
	}



	namespace {
		sst::expr_ptr analyze_new_variable_right(
			const ast::NewVar & new_var,
			Context & context,
			Scope & scope) {
			
			if(new_var.expression) {
				return analyze_expression(*new_var.expression, context, scope);
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
		Context & context,
		Scope & scope) {

		auto expr = analyze_new_variable_right(new_var, context, scope);
		const auto var = insert_new_var(new_var, scope, expr->type);		
		auto r = conversion_on_assign(std::move(expr), var.type, new_var.location);
		return std::make_unique<sst::NewVar>(0, true, var.address, std::move(r), var.type);
	}
}