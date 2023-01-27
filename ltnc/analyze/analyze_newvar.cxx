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
			
			if(new_var.expression) {
				return analyze_expression(*new_var.expression, context, scope);
			}
			if(new_var.type) {
				const auto type = instantiate_type(*new_var.type, scope);
				return generate_default_value(type, new_var.location);
			}
			return std::make_unique<sst::Null>(type::Any{});
		}
	}


	namespace {
		sst::bind_ptr analyze_binding(
			const ast::Binding & binding,
			Context & context,
			Scope & scope,
			const type::Type & from_type);



		sst::bind_ptr analyze_bind(
			const ast::GroupBinding & binding,
			Context & context,
			Scope & scope,
			const type::Type & from_type) {

			auto sst_binding = std::make_unique<sst::GroupBinding>();
			if(!type::is_tuple(from_type)) throw CompilerError {
				"Can only unpack tuple"
			};
			for(std::size_t i = 0; i < std::size(binding.sub_bindings); ++i) {
				auto type = type::deduce_index(from_type, type::Int{}, i);
				if(type::is_error(type)) throw CompilerError {
					"Cannot unpack tuple element",
					binding.location
				};
				auto sub_binding = analyze_binding(*binding.sub_bindings[i], context, scope, type);
				sst_binding->sub_bindings.push_back(std::move(sub_binding));
			}

			return sst_binding;
		}
		

		
		sst::bind_ptr analyze_bind(
			const ast::VarBinding & binding,
			Context & context,
			Scope & scope,
			const type::Type & from_type) {

			const auto var = scope.insert(binding.name, binding.location, from_type); 
			return std::make_unique<sst::VarBinding>(var.address);
		}



		sst::bind_ptr analyze_binding(
			const ast::Binding & binding,
			Context & context,
			Scope & scope,
			const type::Type & from_type) {

			return ast::visit_binding(binding, [&] (const auto & b) {
				return analyze_bind(b, context, scope, from_type);
			});
		}
	}



	sst::stmt_ptr analyze_stmt(
		const ast::NewVar & new_var,
		Context & context,
		Scope & scope) {

		auto expr = analyze_new_variable_right(new_var, context, scope);
		// auto expr =  analyze_expression(*new_vars.expression, context, scope);
		if(new_var.type) {
			auto decl_type = instantiate_type(*new_var.type, scope);
			auto binding = analyze_binding(*new_var.binding, context, scope, expr->type);
			expr = conversion_on_assign(std::move(expr), decl_type, new_var.location);
			return std::make_unique<sst::NewVar>(
				0, binding->alloc_count(),
				std::move(binding),
				std::move(expr)
			);
		}
		else {
			auto binding = analyze_binding(*new_var.binding, context, scope, expr->type);
			return std::make_unique<sst::NewVar>(
				0, binding->alloc_count(),
				std::move(binding),
				std::move(expr)
			);
		}
	}
}