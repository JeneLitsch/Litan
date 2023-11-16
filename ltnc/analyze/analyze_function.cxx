#include "analyze.hxx"
#include <iostream>
#include "ltnc/print/print.hxx"
#include "stdxx/functional.hxx"
#include "ltnc/sst/expr/Var.hxx"

namespace ltn::c {
	namespace {
		void add_parameters_to_scope(
			const ast::Parameters & parameters,
			Scope & scope,
			const SourceLocation & loc) {
			
			for(const auto & param : parameters.simple) {
				scope.insert(param.name, loc);
			}

			if(parameters.variadic) {
				scope.insert(parameters.variadic->name, loc);
			}
		}



		auto analyze_except(	
			const ast::Except & except,
			Context & context,
			const auto & namespaze) {
			
			MajorScope scope{namespaze, false, context};
			scope.insert(except.errorname, location(except));
			auto body = analyze_statement(*except.body, scope);
			return sst::misc::except(except.errorname, std::move(body));
		}
	}



	sst::func_ptr analyze_function(
		const ast::Function & fx,
		Scope & scope,
		std::optional<Label> override_label,
		const std::vector<std::unique_ptr<ast::Var>> & captures) {

		const auto label = override_label.value_or(make_function_label(fx));

		auto & context = scope.get_context();

		add_parameters_to_scope(fx.parameters, scope, location(fx));

		for(const auto & capture : captures) {
			scope.insert(capture->name, location(*capture));
		}

		auto body = analyze_statement(*fx.body, scope);

		auto sst_fx = sst::decl::function(fx.name, fx.namespaze, std::move(body), label);

		sst_fx->is_const = fx.is_const; 
		sst_fx->is_extern = fx.is_extern; 
		sst_fx->is_private = fx.is_private;

		if(fx.except) {
			sst_fx->except = analyze_except(*fx.except, context, fx.namespaze);
		} 

		return sst_fx;
	}



	sst::func_ptr analyze_functional(
		const ast::Function & functional,
		FunctionScope & scope,
		std::optional<Label> override_label,
		const std::vector<std::unique_ptr<ast::Var>> & captures) {

		if(auto fx = as<const ast::Function>(functional)) {
			return analyze_function(*fx, scope, override_label, captures);
		}
		
		throw CompilerError {
			"Unknown functional declaration",
			location(functional)
		};
	}
}