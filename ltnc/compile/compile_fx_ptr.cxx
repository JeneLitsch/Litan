#include "compile.hxx"
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
			CompilerInfo & info) {

			const auto fx = info.fx_table.resolve(
				fx_ptr.name,
				scope.get_namespace(),
				fx_ptr.namespaze,
				fx_ptr.placeholders);

			if(!fx) throw undefined_function(fx_ptr.name, fx_ptr);

			info.fx_queue.stage_function(*fx);

			return std::tuple{fx, fx->id};
		}



		auto resolve_fx_ptr_template(
			const ast::FxPointer & fx_ptr,
			Scope & scope,
			CompilerInfo & info) {
			const auto tmpl = get_template(
				fx_ptr.name,
				fx_ptr.namespaze,
				fx_ptr.placeholders,
				fx_ptr.template_arguements.size(),
				fx_ptr.location,
				info,
				scope
			);

			const auto arguments = stx::fx::mapped(instantiate_type)(
				fx_ptr.template_arguements,
				scope
			);

			info.fx_queue.stage_template(*tmpl, arguments);
			
			add_template_args(
				scope,
				tmpl->template_parameters,
				fx_ptr.template_arguements);

			const auto id = make_template_id(*tmpl->fx, arguments);
			const auto * fx = &*tmpl->fx;

			if(fx->parameters.size() != fx_ptr.placeholders) {
				throw undefined_function(fx->name, fx_ptr);
			}

			return std::tuple{fx,id};
		}



		bool refers_to_template(const ast::FxPointer & fx_ptr) {
			return !fx_ptr.template_arguements.empty();
		}



		auto resolve_fx_ptr(
			const ast::FxPointer & fx_ptr,
			Scope & scope,
			CompilerInfo & info) {
			if(refers_to_template(fx_ptr)) {
				return resolve_fx_ptr_template(fx_ptr, scope, info);
			}
			else {
				return resolve_fx_ptr_normal(fx_ptr, scope, info);
			}
		}
	}


	ExprResult compile_expr(
		const ast::FxPointer & fx_ptr,
		CompilerInfo & info,
		Scope & scope) {

		MinorScope inner_scope{&scope};
		auto [funtional, id] = resolve_fx_ptr(fx_ptr, inner_scope, info);
		const auto & namespaze = inner_scope.get_namespace();

		guard_private(*funtional, namespaze, fx_ptr.location);

		InstructionBuffer buf;
		buf << inst::newfx(id, fx_ptr.placeholders);

		const auto return_type 
			= instantiate_type(funtional->return_type, inner_scope);
		
		const auto parameter_types
			= instantiate_parameters(funtional->parameters, inner_scope);

		return ExprResult { 
			.code = buf,
			.deduced_type = type::FxPtr{
				.return_type = return_type,
				.parameter_types = parameter_types,
			},
		};
	}
}