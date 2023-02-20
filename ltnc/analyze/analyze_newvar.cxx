#include "analyze.hxx"
#include "ltnc/type/traits.hxx"
#include <iostream>
#include "conversion.hxx"
#include "ltnc/type/traits.hxx"
#include "default_value.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr analyze_new_variable_right(
			const ast::NewVar & new_var,
			Context & context,
			Scope & scope) {
			
			if(new_var.expr) {
				auto expr = analyze_expression(*new_var.expr, context, scope);
				if(new_var.type) {
					auto decl_type = instantiate_type(*new_var.type, scope);
					expr = conversion_on_assign(std::move(expr), decl_type, location(new_var));
				}
				return expr;
			}
			if(new_var.type) {
				const auto type = instantiate_type(*new_var.type, scope);
				return generate_default_value(type, location(new_var));
			}
			return std::make_unique<sst::Null>(type::Any{});
		}
	}



	sst::stmt_ptr analyze_stmt(
		const ast::NewVar & new_var,
		Context & context,
		Scope & scope) {

		auto expr = analyze_new_variable_right(new_var, context, scope);
		auto binding = analyze_binding(*new_var.binding, context, scope, expr->type);
		return std::make_unique<sst::Assign>(std::move(binding), std::move(expr));
	}
}