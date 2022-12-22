#include "analyze.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	namespace {
		auto default_any() {
			return std::make_unique<sst::Null>(type::Null{}); 
		}



		auto default_optional() {
			return std::make_unique<sst::Null>(type::Null{}); 
		}


		
		auto default_bool() {
			return std::make_unique<sst::Bool>(false, type::Bool{});
		}


		
		auto default_int() {
			return std::make_unique<sst::Integer>(0, type::Int{});
		}



		auto default_float() {
			return std::make_unique<sst::Float>(0.0, type::Float{});
		}



		auto default_string() {
			return std::make_unique<sst::String>("", type::String{});
		}
		


		auto default_array() {
			return std::make_unique<sst::Array>(type::Array{});
		}
		



		sst::expr_ptr generate_default_value(
			const type::Type & type,
			const SourceLocation & location) {
			if(type::is_any(type)) return default_any();
			if(type::is_optional(type)) return default_optional();
			if(type::is_bool(type)) return default_bool(); 
			if(type::is_int(type)) return default_int(); 
			if(type::is_float(type)) return default_float();
			if(type::is_string(type)) return default_string();
			if(type::is_array(type)) return default_array();
			throw CompilerError {
				"Cannot default initialize type " + type::to_string(type),
				location
			};
		}


		sst::expr_ptr analyze_new_variable_right(
			const ast::NewVar & new_var,
			Context & context,
			Scope & scope) {
			
			if(new_var.expression) {
				return analyze_expression(*new_var.expression, context, scope);
			}
			auto imcomplete = std::get_if<type::IncompleteType>(&new_var.type);
			if(imcomplete) {
				const auto type = instantiate_type(*imcomplete, scope);
				return generate_default_value(type, new_var.location);
			}
			return std::make_unique<sst::Null>(type::Any{});
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