#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include "stdxx/iife.hxx"
#include <string_view>

namespace ltn::c {
	namespace {
		std::vector<type::Type> instantiate_parameters(
			const ast::Parameters & parameters,
			Scope & scope) {
			std::vector<type::Type> parameter_types;
			for(const auto & parameter : parameters) {
				const auto type = instantiate_type(parameter.type, scope);
				parameter_types.push_back(type);
			}
			return parameter_types;
		}



		auto resolve_fx_ptr_normal(
			const ast::FxPointer & fx_ptr,
			Scope & scope,
			Context & context) {

			const auto fx = context.fx_table.resolve(
				fx_ptr.name,
				scope.get_namespace(),
				fx_ptr.namespaze,
				stx::fx::mapped(instantiate_type)(fx_ptr.function_types, scope)		
			);

			if(!fx) throw undefined_function(fx_ptr.name, fx_ptr);

			context.fx_queue.stage_function(*fx);

			const auto label = make_function_label(*fx);

			return std::tuple{fx, label};
		}



		auto resolve_fx_ptr_template(
			const ast::FxPointer & fx_ptr,
			Scope & scope,
			Context & context) {
			const auto tmpl = get_template(
				fx_ptr.name,
				fx_ptr.namespaze,
				fx_ptr.function_types.size(),
				fx_ptr.template_args.size(),
				fx_ptr.location,
				context,
				scope
			);

			const auto template_args = stx::fx::mapped(instantiate_type)(
				fx_ptr.template_args,
				scope
			);

			context.fx_queue.stage_template(*tmpl, template_args);
			
			add_template_args(
				scope,
				tmpl->template_parameters,
				fx_ptr.template_args);

			const auto fx_label = make_function_label(*tmpl->fx);
			const auto tmpl_label = derive_template(fx_label, template_args);
			const auto * fx = &*tmpl->fx;

			if(fx->parameters.size() != fx_ptr.function_types.size()) {
				throw undefined_function(fx->name, fx_ptr);
			}

			return std::tuple{fx,tmpl_label};
		}



		bool refers_to_template(const ast::FxPointer & fx_ptr) {
			return !fx_ptr.template_args.empty();
		}



		auto resolve_fx_ptr(
			const ast::FxPointer & fx_ptr,
			Scope & scope,
			Context & context) {
			if(refers_to_template(fx_ptr)) {
				return resolve_fx_ptr_template(fx_ptr, scope, context);
			}
			else {
				return resolve_fx_ptr_normal(fx_ptr, scope, context);
			}
		}
	}


	sst::expr_ptr analyze_expr(
		const ast::FxPointer & fx_ptr,
		Context & context,
		Scope & scope) {

		MinorScope inner_scope{&scope};
		auto [funtional, label] = resolve_fx_ptr(fx_ptr, inner_scope, context);

		const auto return_type 
			= instantiate_type(funtional->return_type, inner_scope);
		
		const auto parameter_types
			= instantiate_parameters(funtional->parameters, inner_scope);

		const auto type = type::FxPtr {
			.return_type = return_type,
			.parameter_types = parameter_types,
		};

		return std::make_unique<sst::FxPointer>(label, funtional->parameters.size(), type);
	}
}