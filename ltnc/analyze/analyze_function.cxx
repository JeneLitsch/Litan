#include "analyze.hxx"
#include <iostream>
#include "ltnc/print/print.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	namespace {

		sst::Parameters analyze_parameters(
			const ast::Parameters & parameters,
			Scope & scope,
			const SourceLocation & loc) {
			
			sst::Parameters p;
			for(const auto & param : parameters) {
				auto sst_param = sst::Parameter {
					.name = param.name,
					.type = instantiate_type(param.type, scope)
				};
				scope.insert(sst_param.name, loc, sst_param.type);
				p.push_back(sst_param);
			}
			return p;
		}



		auto analyze_except(	
			const ast::Except & except,
			Context & context,
			const auto & namespaze) {
			
			MajorScope scope{namespaze, false};
			scope.insert(except.errorname, location(except));
			auto body = analyze_statement(*except.body, context, scope);
			return std::make_unique<sst::Except>(
				except.errorname,
				std::move(body)
			);
		}



		sst::func_ptr analyze_function(
			const ast::Function & fx,
			Context & context,
			Scope & scope,
			std::vector<std::unique_ptr<sst::Var>> capture,
			std::optional<Label> override_label = std::nullopt) {

			const auto label = override_label.value_or(
				make_function_label(fx.namespaze, fx.name, fx.parameters.size())
			);

			auto parameters = analyze_parameters(fx.parameters, scope, location(fx));

			auto body = analyze_statement(*fx.body, context, scope);

			auto sst_fx = std::make_unique<sst::Function>(
				label,
				fx.name,
				fx.namespaze,
				parameters,
				std::move(body),
				instantiate_type(fx.return_type, scope)
			);

			sst_fx->is_const = fx.is_const; 
			sst_fx->is_extern = fx.is_extern; 
			sst_fx->is_private = fx.is_private;
			sst_fx->capture = std::move(capture);

			if(fx.except) {
				sst_fx->except = analyze_except(*fx.except, context, fx.namespaze);
			} 

			return sst_fx;
		}



		sst::func_ptr analyze_build_in_function(
			const ast::BuildIn & fx,
			Scope & scope,
			std::optional<Label> override_label) {

			const auto label = override_label.value_or(
				make_function_label(fx.namespaze, fx.name, fx.parameters.size())
			);

			auto parameters = analyze_parameters(fx.parameters, scope, location(fx));

			auto sst_fx = std::make_unique<sst::BuildIn>(
				label,
				fx.name,
				fx.namespaze,
				parameters,
				fx.key,
				instantiate_type(fx.return_type, scope)
			);

			sst_fx->is_const   = fx.is_const; 
			sst_fx->is_extern  = fx.is_extern; 
			sst_fx->is_private = fx.is_private;

			return sst_fx;
		}
	}



	sst::func_ptr analyze_functional(
		const ast::Functional & functional,
		Context & context,
		Scope & scope,
		std::optional<Label> override_label) {

		if(auto fx = as<const ast::Function>(functional)) {
			return analyze_function(*fx, context, scope, {}, override_label);
		}
		if(auto fx = as<const ast::BuildIn>(functional)) {
			return analyze_build_in_function(*fx, scope, override_label);
		}
		throw CompilerError {
			"Unknown functional declaration",
			location(functional)
		};
	}



	sst::func_ptr analyze_functional(
		const ast::Functional & functional,
		Context & context) {

		FunctionScope scope {
			functional.namespaze,
			functional.is_const,
		};
		scope.set_return_type(instantiate_type(functional.return_type, scope));
		return analyze_functional(functional, context, scope, std::nullopt);
	}



	sst::func_ptr analyze_function_template(
		const ast::FunctionTemplate & tmpl,
		Context & context,
		const std::vector<type::Type> & arguments) {

		FunctionScope scope { tmpl.fx->namespaze, tmpl.fx->is_const };
		add_template_args(scope, tmpl.template_parameters, arguments);
		scope.set_return_type(instantiate_type(tmpl.fx->return_type, scope));
		const auto label = make_template_label(tmpl, arguments);
		return analyze_functional(*tmpl.fx, context, scope, label);
	}



	sst::expr_ptr analyze_expr(
		const ast::Lambda & lambda,
		Context & context,
		Scope & outer_scope) {
		
		const auto & fx = *lambda.fx;
		
		// load captures
		MajorScope inner_scope {
			outer_scope.get_namespace(),
			fx.is_const
		};

		const auto instatiate_param_type = [&] (const auto & param) {
			return instantiate_type(param.type, inner_scope);
		};

		const auto analyze_capture_store = [&] (const auto & capture) {
			auto expr = analyze_expr(*capture, context, outer_scope);
			return stx::static_unique_cast<sst::Var>(std::move(expr));
		};

		const auto analyze_capture_load = [&] (const auto & capture) {
			const auto var = inner_scope.insert(capture->name, location(fx));
			return std::make_unique<sst::Var>(var.address, var.type);
		};

		inner_scope.inherit_types_from(outer_scope);
		
		auto load_captures = stx::fx::map(analyze_capture_load, lambda.captures);

		const auto label = make_lambda_label(lambda);

		auto sst_fx = analyze_function(*lambda.fx, context, inner_scope, std::move(load_captures), label);

		auto store_captures = stx::fx::map(analyze_capture_store, lambda.captures);
		auto parameter_types = stx::fx::map(instatiate_param_type, fx.parameters);

		const auto return_type = type::FxPtr {
			.return_type = instantiate_type(fx.return_type, inner_scope),
			.parameter_types = parameter_types, 
		};

		return std::make_unique<sst::Lambda>(
			stx::static_unique_cast<sst::Function>(std::move(sst_fx)),
			std::move(store_captures),
			instantiate_type(fx.return_type, outer_scope)
		);
	}
}