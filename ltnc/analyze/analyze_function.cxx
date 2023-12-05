#include "analyze.hxx"
#include <iostream>
#include "ltnc/print/print.hxx"
#include "stdxx/functional.hxx"

#include "ltnc/ast/expr/BuildIn.hxx"
#include "ltnc/ast/expr/Var.hxx"

#include "ltnc/sst/expr/Var.hxx"

namespace ltn::c {
	namespace {
		void add_parameters_to_scope(
			const ast::decl::Parameters & parameters,
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
			const ast::decl::Except & except,
			Context & context,
			const auto & namespaze) {
			
			MajorScope scope{namespaze, Qualifiers::none, context};
			scope.insert(except.errorname, location(except));
			auto body = analyze_statement(*except.body, scope);
			return sst::misc::except(except.errorname, std::move(body));
		}
	}



	sst::func_ptr analyze_function(
		const ast::decl::Function & fx,
		FunctionScope & scope,
		std::optional<Label> override_label,
		const std::vector<std::unique_ptr<ast::expr::Var>> & captures) {

		const auto label = override_label.value_or(make_function_label(fx));

		auto & context = scope.get_context();

		add_parameters_to_scope(fx.parameters, scope, location(fx));

		for(const auto & capture : captures) {
			scope.insert(capture->name, location(*capture));
		}

		auto body = analyze_statement(*fx.body, scope);

		auto sst_fx = sst::decl::function(fx.name, fx.namespaze, std::move(body), label);

		sst_fx->qualifiers = fx.qualifiers; 

		if(fx.except) {
			sst_fx->except = analyze_except(*fx.except, context, fx.namespaze);
		} 

		return sst_fx;
	}
}