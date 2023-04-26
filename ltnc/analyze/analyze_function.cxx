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
					.type = analyze_parameter_type(param.type, scope),
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
			
			MajorScope scope{namespaze, false, context};
			scope.insert(except.errorname, location(except));
			auto body = analyze_statement(*except.body, scope);
			return std::make_unique<sst::Except>(
				except.errorname,
				std::move(body)
			);
		}



		sst::func_ptr analyze_build_in_function(
			const ast::BuildIn & fx,
			Scope & scope,
			std::optional<Label> override_label) {

			const auto label = override_label.value_or(make_function_label(fx));

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



	sst::func_ptr analyze_function(
		const ast::Function & fx,
		Scope & scope,
		std::optional<Label> override_label,
		const std::vector<std::unique_ptr<ast::Var>> & captures) {

		const auto label = override_label.value_or(make_function_label(fx));

		auto & context = scope.get_context();

		auto parameters = analyze_parameters(fx.parameters, scope, location(fx));

		for(const auto & capture : captures) {
			scope.insert(capture->name, location(*capture));
		}

		auto body = analyze_statement(*fx.body, scope);

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

		if(fx.except) {
			sst_fx->except = analyze_except(*fx.except, context, fx.namespaze);
		} 

		return sst_fx;
	}



	sst::func_ptr analyze_functional(
		const ast::Functional & functional,
		FunctionScope & scope,
		std::optional<Label> override_label,
		const std::vector<std::unique_ptr<ast::Var>> & captures) {

		scope.set_return_type(instantiate_type(functional.return_type, scope));

		if(auto fx = as<const ast::Function>(functional)) {
			return analyze_function(*fx, scope, override_label, captures);
		}
		
		if(auto fx = as<const ast::BuildIn>(functional)) {
			return analyze_build_in_function(*fx, scope, override_label);
		}

		throw CompilerError {
			"Unknown functional declaration",
			location(functional)
		};
	}
}