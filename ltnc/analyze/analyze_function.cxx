#include "analyze.hxx"
#include <iostream>
#include "ltnc/print/print.hxx"
#include "labels.hxx"

namespace ltn::c {
	namespace {

		sst::Parameters analyze_parameters(const ast::Parameters & parameters, Scope & scope, const SourceLocation & loc) {
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
			scope.insert(except.errorname, except.location);
			auto body = analyze_statement(*except.body, context, scope);
			return std::make_unique<sst::Except>(
				except.errorname,
				std::move(body)
			);
		}

		// compiles Litan function
		sst::func_ptr analyze_function(
			const ast::Function & fx,
			Context & context,
			Scope & scope,
			std::vector<std::unique_ptr<sst::Var>> capture,
			std::optional<std::string> override_id = std::nullopt) {

			const auto id = override_id.value_or(fx.id);
			auto parameters = analyze_parameters(fx.parameters, scope, fx.location);
			auto body = analyze_statement(*fx.body, context, scope);
			auto sst_fx = std::make_unique<sst::Function>(
				id,
				fx.name,
				fx.namespaze,
				parameters,
				std::move(body),
				instantiate_type(fx.return_type, scope)
			);
			sst_fx->c0nst = fx.c0nst; 
			sst_fx->init = fx.init; 
			sst_fx->pr1vate = fx.pr1vate;
			sst_fx->capture = std::move(capture);
			if(fx.except) {
				sst_fx->except = analyze_except(*fx.except, context, fx.namespaze);
			} 

			return sst_fx;
		}




		// compiles asm_function
		sst::func_ptr analyze_build_in_function(
			const ast::BuildIn & fx,
			Scope & scope,
			std::optional<std::string> override_id) {
			
			auto parameters = analyze_parameters(fx.parameters, scope, fx.location);
			auto sst_fx = std::make_unique<sst::BuildIn>(
				override_id.value_or(fx.id),
				fx.name,
				fx.namespaze,
				parameters,
				fx.key,
				instantiate_type(fx.return_type, scope)
			);
			sst_fx->c0nst = fx.c0nst; 
			sst_fx->init = fx.init; 
			sst_fx->pr1vate = fx.pr1vate;

			return sst_fx;
		}
	}



	// compiles functional node
	sst::func_ptr analyze_functional(
		const ast::Functional & functional,
		Context & context,
		Scope & scope,
		std::optional<std::string> override_id) {

		if(auto fx = as<const ast::Function>(functional)) {
			return analyze_function(*fx, context, scope, {}, override_id);
		}
		if(auto fx = as<const ast::BuildIn>(functional)) {
			return analyze_build_in_function(*fx, scope, override_id);
		}
		throw CompilerError{
			"Unknown functional declaration",
			functional.location};
	}


	// compiles functional node
	sst::func_ptr analyze_functional(
		const ast::Functional & functional,
		Context & context) {

		FunctionScope scope {
			functional.namespaze,
			functional.c0nst,
		};
		scope.set_return_type(instantiate_type(functional.return_type, scope));
		return analyze_functional(functional, context, scope, std::nullopt);
	}



	sst::func_ptr analyze_function_template(
		const ast::FunctionTemplate & tmpl,
		Context & context,
		const std::vector<type::Type> & arguments) {

		FunctionScope scope {
			tmpl.fx->namespaze,
			tmpl.fx->c0nst,
		};

		add_template_args(scope, tmpl.template_parameters, arguments);
		scope.set_return_type(instantiate_type(tmpl.fx->return_type, scope));
		const auto id = make_template_id(*tmpl.fx, arguments);
		return analyze_functional(*tmpl.fx, context, scope, id);
	}



	sst::expr_ptr analyze_expr(
		const ast::Lambda & lm,
		Context & context,
		Scope & outer_scope) {
		
		const auto & fx = *lm.fx;
		
		// load captures
		MajorScope inner_scope {
			outer_scope.get_namespace(),
			fx.c0nst
		};

		inner_scope.inherit_types_from(outer_scope);
		
		std::vector<std::unique_ptr<sst::Var>> load_captures;
		for(const auto & capture : lm.captures) {
			const auto var = inner_scope.insert(capture->name, fx.location);
			auto expr = std::make_unique<sst::Var>(var.address, var.type);
			load_captures.push_back(std::move(expr));
		}

		const auto id = unique_lambda_label();

		// compile function
		auto sst_fx = analyze_function(*lm.fx, context, inner_scope, std::move(load_captures), id);

		// store captures
		std::vector<std::unique_ptr<sst::Var>> store_captures;
		for(const auto & capture : lm.captures) {
			auto expr = analyze_expr(*capture, context, outer_scope);
			auto var = stx::static_unique_cast<sst::Var>(std::move(expr));
			store_captures.push_back(std::move(var));
		}


		std::vector<type::Type> parameter_types;
		for(const auto & parameter : fx.parameters) {
			const auto type = instantiate_type(parameter.type, inner_scope);
			parameter_types.push_back(type);
		}

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