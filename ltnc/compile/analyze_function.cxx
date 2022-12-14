#include "compile.hxx"
#include <iostream>
#include "build_in/build_in.hxx"
#include "ltnc/print/print.hxx"

namespace ltn::c {
	namespace {

		inst::Inst parameters(const ast::Functional & fx, Scope & scope) {
			for(const auto & param : fx.parameters) {
				const auto type = instantiate_type(param.type, scope);
				scope.insert(param.name, fx.location, type);
			}
			const auto arity = static_cast<std::uint8_t>(fx.parameters.size());
			return inst::parameters(arity);
		}


		const std::string jumpmark_except(const std::string_view name) {
			std::stringstream ss;
			ss << "_" << name << "_EXCEPT";
			return ss.str(); 
		}

		const std::string jumpmark_skip(const std::string_view name) {
			std::stringstream ss;
			ss << "_" << name << "_SKIP";
			return ss.str(); 
		}


		sst::stmt_ptr analyze_body(
			const auto & fx,
			CompilerInfo & info,
			Scope & scope) {

			InstructionBuffer buf;
			if(fx.body) {
				const auto body = analyze_statement(*fx.body, info, scope);
				for(std::size_t i = 0; i < body.var_count; i++) {
					buf << inst::makevar();
				}
				buf << body.code;
			}
			return buf;
		}



		auto analyze_except(	
			const ast::Except & except,
			const std::string & fxid,
			CompilerInfo & info,
			const auto & namespaze) {
			
			MajorScope scope{namespaze, false};
			scope.insert(except.errorname, except.location);
			auto body = analyze_statement(*except.body, info, scope);
			return std::make_unique<sst::Except>(
				except.errorname,
				std::move(body)
			);
		}

		// compiles Litan function
		sst::func_ptr analyze_function(
			const ast::Function & fx,
			CompilerInfo & info,
			Scope & scope,
			std::vector<sst::stmt_ptr> capture,
			std::optional<std::string> override_id = std::nullopt) {
			
			InstructionBuffer buf;

			const auto id = override_id.value_or(fx.id);
			auto body = analyze_body(fx, info, scope);
			auto sst_fx = std::make_unique<sst::Function>(
				fx.name,
				fx.namespaze,
				fx.parameters,
				std::move(body),
				instantiate_type(fx.return_type, scope)
			);
			sst_fx->c0nst = fx.c0nst; 
			sst_fx->init = fx.init; 
			sst_fx->pr1vate = fx.pr1vate;
			sst_fx->capture = std::move(capture);
			if(fx.except) {
				sst_fx->except = analyze_except(*fx.except, id, info, fx.namespaze);
			} 

			return sst_fx;
		}




		// compiles asm_function
		sst::func_ptr analyze_build_in_function(
			const ast::BuildIn & fx,
			CompilerInfo & info,
			Scope & scope,
			std::optional<std::string> override_id) {
			
			InstructionBuffer buf;
			const auto * signature = info.fx_table.resolve(
				fx.name,
				fx.namespaze,
				fx.parameters.size());
			
			buf << inst::label(override_id.value_or(signature->id));
			const auto body = resolve_build_in(fx.key); 
			buf << body;
			buf << inst::null();
			buf << inst::retvrn();
			
			auto sst_fx = std::make_unique<sst::BuildIn>(
				fx.name,
				fx.namespaze,
				fx.parameters,
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
		CompilerInfo & info,
		Scope & scope,
		std::optional<std::string> override_id) {

		if(auto fx = as<const ast::Function>(functional)) {
			return analyze_function(*fx, info, scope, {}, override_id);
		}
		if(auto fx = as<const ast::BuildIn>(functional)) {
			return analyze_build_in_function(*fx, info, scope, override_id);
		}
		throw CompilerError{
			"Unknown functional declaration",
			functional.location};
	}


	// compiles functional node
	sst::func_ptr analyze_functional(
		const ast::Functional & functional,
		CompilerInfo & info) {

		FunctionScope scope {
			functional.namespaze,
			functional.c0nst,
		};
		scope.set_return_type(instantiate_type(functional.return_type, scope));
		return analyze_functional(functional, info, scope, std::nullopt);
	}



	sst::func_ptr analyze_function_template(
		const ast::FunctionTemplate & tmpl,
		CompilerInfo & info,
		const std::vector<type::Type> & arguments) {

		FunctionScope scope {
			tmpl.fx->namespaze,
			tmpl.fx->c0nst,
		};

		add_template_args(scope, tmpl.template_parameters, arguments);
		scope.set_return_type(instantiate_type(tmpl.fx->return_type, scope));
		const auto id = make_template_id(*tmpl.fx, arguments);
		return analyze_functional(*tmpl.fx, info, scope, id);
	}



	sst::expr_ptr analyze_expr(
		const ast::Lambda & lm,
		CompilerInfo & info,
		Scope & outer_scope) {
		
		const auto & fx = *lm.fx;
		
		// load captures
		MajorScope inner_scope {
			outer_scope.get_namespace(),
			fx.c0nst };
		
		std::vector<sst::stmt_ptr> load_captures;
		for(const auto & capture : lm.captures) {
			const auto var = inner_scope.insert(capture->name, fx.location);
			load_captures.push_back(std::make_unique<sst::NewVar>(
				1, false, capture->name,
				std::make_unique<sst::Var>(
					var.address, var.type
				), var.type
			));
		}

		// compile function
		auto fx = analyze_function(*lm.fx, info, inner_scope, std::move(load_captures));

		// store captures
		std::vector<sst::expr_ptr> store_captures;
		for(const auto & capture : lm.captures) {
			store_captures.push_back(analyze_expression(*capture, info, outer_scope));
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
			return_type,
			std::move(fx),
			std::move(store_captures),
			fx.return_type
		);
	}
}