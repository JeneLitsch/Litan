#include "analyze.hxx"
#include "ltnc/type/traits.hxx"
#include <iostream>
#include "conversion.hxx"
#include "ltnc/type/traits.hxx"

namespace ltn::c {
	namespace {
		auto default_any(const type::Type & type) {
			return std::make_unique<sst::Null>(type); 
		}



		auto default_optional(const type::Type & type) {
			return std::make_unique<sst::Null>(type); 
		}


		
		auto default_bool(const type::Type & type) {
			return std::make_unique<sst::Bool>(false, type);
		}


		
		auto default_int(const type::Type & type) {
			return std::make_unique<sst::Integer>(0, type);
		}



		auto default_float(const type::Type & type) {
			return std::make_unique<sst::Float>(0.0, type);
		}



		auto default_string(const type::Type & type) {
			return std::make_unique<sst::String>("", type);
		}
		


		auto default_array(const type::Type & type) {
			return std::make_unique<sst::Array>(type);
		}
		


		sst::expr_ptr generate_default_value(
			const type::Type & type,
			const SourceLocation & location) {
			if(type::is_any(type)) return default_any(type);
			if(type::is_optional(type)) return default_optional(type);
			if(type::is_bool(type)) return default_bool(type); 
			if(type::is_int(type)) return default_int(type); 
			if(type::is_float(type)) return default_float(type);
			if(type::is_string(type)) return default_string(type);
			if(type::is_array(type)) return default_array(type);
			throw CompilerError {
				"Cannot default initialize type " + type::to_string(type),
				location
			};
		}



		sst::expr_ptr analyze_new_variable_right(
			const ast::NewVar & new_var,
			Context & context,
			Scope & scope) {
			
			if(new_var.expr) {
				return analyze_expression(*new_var.expr, context, scope);
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
		if(new_var.type) {
			auto decl_type = instantiate_type(*new_var.type, scope);
			expr = conversion_on_assign(std::move(expr), decl_type, location(new_var));
		}
		return std::make_unique<sst::Assign>(std::move(binding), std::move(expr));
	}
}