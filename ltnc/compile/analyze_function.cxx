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


		InstructionBuffer analyze_body(
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



		InstructionBuffer analyze_except(	
			const ast::Except & except,
			const std::string & fxid,
			CompilerInfo & info,
			const auto & namespaze) {
			
			MajorScope scope{namespaze, false};
			scope.insert(except.errorname, except.location);
			InstructionBuffer buf;
			buf << inst::label(jumpmark_except(fxid));
			buf << inst::parameters(1);
			buf << analyze_body(except, info, scope);
			buf << inst::null();
			buf << inst::retvrn();
			return buf;
		}

		// compiles Litan function
		InstructionBuffer analyze_function(
			const ast::Function & fx,
			CompilerInfo & info,
			Scope & scope,
			InstructionBuffer capture,
			std::optional<std::string> override_id = std::nullopt) {
			
			InstructionBuffer buf;

			const auto id = override_id.value_or(fx.id);
			
			buf << inst::label(id);
			buf << capture;
			buf << parameters(fx, scope);
			if(fx.except) buf << inst::trY(jumpmark_except(id));
			buf << analyze_body(fx, info, scope);
			buf << inst::null();
			buf << inst::retvrn();
			if(fx.except) {
				buf << analyze_except(*fx.except, id, info, fx.namespaze);
			} 
			
			return buf;
		}




		// compiles asm_function
		InstructionBuffer analyze_build_in_function(
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
			
			return buf;
		}
	}



	// compiles functional node
	InstructionBuffer analyze_functional(
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
	InstructionBuffer analyze_functional(
		const ast::Functional & functional,
		CompilerInfo & info) {

		FunctionScope scope {
			functional.namespaze,
			functional.c0nst,
		};
		scope.set_return_type(instantiate_type(functional.return_type, scope));
		return analyze_functional(functional, info, scope, std::nullopt);
	}



	InstructionBuffer analyze_function_template(
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
		InstructionBuffer buf;
		
		// Skip
		buf << inst::jump(jumpmark_skip(fx.id));
		
		// load captures
		MajorScope inner_scope {
			outer_scope.get_namespace(),
			fx.c0nst };
		
		InstructionBuffer capture_buf;
		
		for(const auto & capture : lm.captures) {
			const auto var = inner_scope.insert(capture->name, fx.location);
			capture_buf << inst::makevar();
			capture_buf << inst::write_x(var.address);
		}

		// compile function
		buf << analyze_function(*lm.fx, info, inner_scope, capture_buf);

		// Create function pointer
		buf << inst::label(jumpmark_skip(fx.id));
		buf << inst::newfx(fx.id, fx.parameters.size());
		
		// store captures
		for(const auto & capture : lm.captures) {
			buf << analyze_expression(*capture, info, outer_scope).code;
			buf << inst::capture();
		}


		std::vector<type::Type> parameter_types;
		for(const auto & parameter : fx.parameters) {
			const auto type = instantiate_type(parameter.type, inner_scope);
			parameter_types.push_back(type);
		}

		return {
			.code = buf,
			.deduced_type = type::FxPtr {
				.return_type = instantiate_type(fx.return_type, inner_scope),
				.parameter_types = parameter_types, 
			}
		};
	}
}