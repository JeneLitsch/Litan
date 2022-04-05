#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	namespace {
		CompilerError undefined_function(
			const std::string_view & name,
			const ast::Node & node) {
			std::stringstream ss;
			ss << "Function " << name << " is not defined";
			return CompilerError { ss.str(), node.location };
		}



		CompilerError undefined_enum(
			const ast::GlobalValue & node) {
			std::stringstream ss;
			ss << "Global value " << node.name << " is not defined";
			return CompilerError { ss.str(), node.location };
		}



		ExprCode read_local_variable(const Variable & var) {
			std::stringstream ss;
			ss << inst::read_x(var.address);
			return ExprCode{ ss.str() };
		}



		ExprCode read_global_variable(const ast::Global & global, CompilerInfo & info) {
			Scope s{global.namespaze, false};
			return expression(*global.expr, info, s);
		}



		ExprCode call_parameters(const auto & parameters, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			for(const auto & param : parameters) {
				ss << compile::expression(*param, info, scope).code;
			}
			return {ss.str()};
		}



		namespace {
			bool is_inner_namespace(
				const ast::Namespace & call_ns,
				const ast::Namespace & fx_ns) {
				if(fx_ns.size() > call_ns.size()) return false;
				for(std::size_t i = 0; i < fx_ns.size(); i++) {
					if(call_ns[i] != fx_ns[i]) {
						return false;
					}
				}
				return true;
			}


			void guard_private(
				const ast::Functional * fx,
				const ast::Namespace & call_ns,
				const SourceLocation & loc) {
				if(
					fx &&
					fx->pr1vate &&
					!is_inner_namespace(call_ns, fx->namespaze)) {
					throw CompilerError{
						"Function is not visible in current scope",
						loc
					};
				}
			}
		}
	}



	// compiles an variable read accessc
	ExprCode read_variable(const ast::Var & expr, CompilerInfo & info, Scope & scope) {
		try {
			const auto var = scope.resolve(expr.name, expr.location);
			return read_local_variable(var);
		}
		catch(const CompilerError & error) {
			const auto & name = expr.name;
			const auto & namespaze = scope.get_namespace();
			if(auto global = info.global_table.resolve(name, namespaze)) {
				return read_global_variable(*global, info);
			}
			throw error;
		}
	}

	

	ExprCode read_member_access(
		const ast::Member & access,
		CompilerInfo & info,
		Scope & scope) {

		std::stringstream ss;
		ss << expression(*access.expr, info, scope).code;
		const auto id = info.member_table.get_id(access.name);
		ss << inst::member_read(id);
		return ExprCode{ ss.str() };
	}



	// compiles int literal
	ExprCode integer(const ast::Integer & expr) {
		return ExprCode{inst::newi(expr.value) };
	}



	// compiles float literal
	ExprCode floating(const ast::Float & expr) {
		return ExprCode{ inst::newf(expr.value) };
	}



	// compiles bool literal
	ExprCode boolean(const ast::Bool & expr) {
		const auto inst = (expr.value ? inst::truE : inst::falsE);
		return ExprCode{ std::string(inst) };
	}



	// compiles null literal
	ExprCode null(const ast::Null &) {
		return ExprCode{ std::string(inst::null) };
	}


	// compiles bool literal
	ExprCode character(const ast::Char & expr) {
		return ExprCode{ inst::newc(expr.value) };
	}



	// compiles string literal
	ExprCode string(const ast::String & expr) {
		return ExprCode{ inst::newstr(expr.value) };
	}



	// compiles array literal
	ExprCode array(const ast::Array & array, CompilerInfo & info, Scope & scope) {
		std::stringstream ss;
		for(const auto & elem : array.elements) {
			ss << expression(*elem, info, scope).code;
		}
		ss << inst::newarr(array.elements.size());
		return ExprCode{ ss.str() };
	}



	ExprCode global_value(
		const ast::GlobalValue & global_value,
		CompilerInfo & info,
		Scope & scope) {

		const auto enym = info.global_table.resolve(
			global_value.name,
			scope.get_namespace(),
			global_value.namespaze);
		
		if(!enym) {
			throw undefined_enum(global_value);
		}

		return read_global_variable(*enym, info);
	}


	// compiles function call fx(...)
	ExprCode call(const ast::Call & call, CompilerInfo & info, Scope & scope) {
		// resolve function
		const auto fx = info.fx_table.resolve(
			call.name,
			scope.get_namespace(),
			call.namespaze,
			call.parameters.size());
		
		if(!fx) {
			throw undefined_function(call.name, call);
		}

		guard_private(fx, scope.get_namespace(), call.location);
		
		if(scope.is_const() && !fx->c0nst) {
			throw CompilerError {
				"Cannot call non-const function from a const functions",
				call.location};
		}

		std::stringstream ss;
		ss << call_parameters(call.parameters, info, scope).code;
		ss << inst::call(fx->id);
		return ExprCode{ ss.str() };
	}



	ExprCode fxPointer(
		const ast::FxPointer & ptr,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto fx = info.fx_table.resolve(
			ptr.name,
			scope.get_namespace(),
			ptr.namespaze,
			ptr.placeholders);

		if(!fx) {
			throw undefined_function(ptr.name, ptr);
		}

		guard_private(fx, scope.get_namespace(), ptr.location);

		std::stringstream ss;
		ss << inst::newfx(fx->id, ptr.placeholders);
		return ExprCode{ss.str() };
	}



	// compiles index read operation
	ExprCode index(const ast::Index & index, CompilerInfo & info, Scope & scope) {
		const auto arr = expression(*index.expression, info, scope);
		const auto idx = expression(*index.index, info, scope);
		std::stringstream ss;
		ss	<< arr.code
			<< idx.code
			<< inst::at;
		return ExprCode{ss.str() };
	}



	ExprCode iife(const ast::Iife & iife, CompilerInfo & info, Scope & outer_scope) {
		const auto jumpmark = make_jump_id("IIFE");
		Scope inner_scope{&outer_scope};
		inner_scope.set_return(jumpmark);
		std::ostringstream ss;
		ss << compile::statement(*iife.stmt, info, inner_scope).code;
		ss << inst::null;
		ss << inst::jumpmark(jumpmark);
		return {ss.str()};
	}
}