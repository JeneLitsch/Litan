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
		auto except = fx.except ? analyze_except(*fx.except, info, scope) : nullptr;
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


	std::unique_ptr<sst::BuildIn> analyze_buildin(const ast::BuildIn & fx, CompilerInfo & info, Scope & scope) {
		auto parameters = analyze_parameters(fx.parameters, info, scope);
		auto sst_fx = stx::make_unique<sst::BuildIn>(
			fx.name,
			fx.namespaze,
			parameters,
			fx.key,
			fx.return_type,
			fx.location
		);

		sst_fx->c0nst = fx.c0nst;
		sst_fx->pr1vate = fx.pr1vate;
		sst_fx->init = fx.init;

		return sst_fx;
	}


	sst::func_ptr analyze_functional(const ast::Functional & node, CompilerInfo & info) {
		MajorScope scope{{}, node.c0nst};
		if(auto fx = as<ast::Function>(node)) {
			return analyze_function(*fx, info, scope);
		}
		if(auto bi = as<ast::BuildIn>(node)) {
			return analyze_buildin(*bi, info, scope);
		}
		throw std::runtime_error {
			"Cannot analyze unknown functional node"
		};
	}


	sst::ftmp_ptr analyze_function_template(const ast::FunctionTemplate & node, CompilerInfo & info) {
		auto fx = analyze_functional(*node.fx, info);
		return stx::make_unique<sst::FunctionTemplate>(
			std::move(fx),
			node.template_parameters,
			node.location
		);
	}
}