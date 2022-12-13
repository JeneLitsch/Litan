#include "compile.hxx"

namespace ltn::c {
	auto analyze_except(const ast::Except & except, CompilerInfo & info, Scope & scope) {
		auto body = analyze_statement(*except.body, info, scope);
		return stx::make_unique<sst::Except>(
			except.errorname,
			std::move(body),
			except.location
		);
	}

	auto analyze_parameters(const ast::Parameters & parameters, CompilerInfo & info, Scope & scope) {
		sst::Parameters sst_parameters;
		for(const auto & p : parameters) {
			sst_parameters.push_back(sst::Parameter{
				.name = p.name,
				.type = p.type,
			});
		}
		return sst_parameters;
	}

	
	std::unique_ptr<sst::Function> analyze_function(const ast::Function & fx, CompilerInfo & info, Scope & scope) {
		auto body = analyze_statement(*fx.body, info, scope);
		auto except = analyze_except(*fx.except, info, scope);
		auto parameters = analyze_parameters(fx.parameters, info, scope);
		auto sst_fx = stx::make_unique<sst::Function>(
			fx.name,
			fx.namespaze,
			parameters,
			std::move(body),
			fx.return_type,
			fx.location
		);

		sst_fx->except = std::move(except);
		sst_fx->c0nst = fx.c0nst;
		sst_fx->pr1vate = fx.pr1vate;
		sst_fx->init = fx.init;

		return sst_fx;
	}
}