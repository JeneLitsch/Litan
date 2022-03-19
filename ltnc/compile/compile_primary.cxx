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



		// compiles int literal
		ExprCode integer(const auto & expr) {
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



		ExprCode read_local_variable(const Variable & var) {
			std::stringstream ss;
			ss << inst::read_x(var.address);
			return ExprCode{ ss.str() };
		}



		ExprCode read_global_variable(const GlobalSignature & global, CompilerInfo & info) {
			Scope s{global.namespaze};
			return expression(*global.constant, info, s);
		}



		ExprCode call_parameters(const auto & parameters, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			for(const auto & param : parameters) {
				ss << compile::expression(*param, info, scope).code;
			}
			return {ss.str()};
		}


		ExprCode invoke_lambda(
			const ast::Call & call,
			CompilerInfo & info,
			Scope & scope) {
			
			std::stringstream ss;
			ss << call_parameters(call.parameters, info, scope).code;
			ss << inst::newarr(call.parameters.size());
			ss << inst::invoke;
			return ExprCode{ ss.str() };
		}


		std::optional<ExprCode> invoke_local(
			const ast::Call & call,
			CompilerInfo & info,
			Scope & scope) {
			
			if(call.namespaze.empty()) {
				try {
					const auto var = scope.resolve(call.name, call.location);
					std::stringstream ss;
					ss << read_local_variable(var).code;
					ss << invoke_lambda(call, info, scope).code;
					return ExprCode{ ss.str() };
				}
				catch(...){}
			}
			return std::nullopt;
		}



		std::optional<ExprCode> call_function(
			const ast::Call & call,
			CompilerInfo & info,
			Scope & scope) {
			// resolve function
			const auto fx = info.fx_table.resolve(
				call.name,
				scope.get_namespace(),
				call.namespaze,
				call.parameters.size());
			
			if(fx) {
				std::stringstream ss;
				ss << call_parameters(call.parameters, info, scope).code;
				ss << inst::call(fx->id);
				return ExprCode{ ss.str() };
			}
			return std::nullopt;
		}



		std::optional<ExprCode> invoke_global(
			const ast::Call & call,
			CompilerInfo & info,
			Scope & scope) {

			const auto & name = call.name;
			const auto & namespaze = scope.get_namespace();
			if(auto global = info.global_table.resolve(name, namespaze)) {
				std::stringstream ss;
				ss << read_global_variable(*global, info).code;
				ss << invoke_lambda(call, info, scope).code;
				return ExprCode{ ss.str() };
			}
			return std::nullopt;
		}



		// compiles function call fx(...)
		ExprCode call(const ast::Call & call, CompilerInfo & info, Scope & scope) {
			if(const auto code = invoke_local(call, info, scope)) return *code;
			if(const auto code = call_function(call, info, scope)) return *code;
			if(const auto code = invoke_global(call, info, scope)) return *code;
			throw undefined_function(call.name, call);
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
			const auto jumpmark = make_jump_id("IIFE", info);
			Scope inner_scope{&outer_scope};
			inner_scope.set_return(jumpmark);
			std::ostringstream ss;
			ss << compile::statement(*iife.stmt, info, inner_scope).code;
			ss << inst::null;
			ss << inst::jumpmark(jumpmark);
			return {ss.str()};
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



	// compiles Primary expression
	ExprCode primary(const ast::Primary & expr, CompilerInfo & info, Scope & scope) {
		if(auto expr_ = as<ast::Integer>(expr)) {
			return integer(*expr_);
		}
		if(auto expr_ = as<ast::Enum>(expr)) {
			return integer(*expr_);
		} 
		if(auto expr_ = as<ast::Float>(expr)) {
			return floating(*expr_);
		} 
		if(auto expr_ = as<ast::Bool>(expr)) {
			return boolean(*expr_);
		}
		if(auto expr_ = as<ast::Char>(expr)) {
			return character(*expr_);
		}
		if(auto expr_ = as<ast::Null>(expr)) {
			return null(*expr_);
		} 
		if(auto expr_ = as<ast::String>(expr)) {
			return string(*expr_);
		} 
		if(auto expr_ = as<ast::Array>(expr)) {
			return array(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Call>(expr)) {
			return call(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Var>(expr)) {
			return read_variable(*expr_, info, scope);
		} 	
		if(auto expr_ = as<ast::Index>(expr)) {
			return index(*expr_, info, scope);
		}	
		if(auto expr_ = as<ast::Lambda>(expr)) {
			return lambda(*expr_, info, scope);
		}	
		if(auto expr_ = as<ast::FxPointer>(expr)) {
			return fxPointer(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Member>(expr)) {
			return read_member_access(*expr_, info, scope);
		}		
		if(auto expr_ = as<ast::Iife>(expr)) {
			return compile::iife(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::GlobalValue>(expr)) {
			return compile::global_value(*expr_, info, scope);
		} 
		throw CompilerError{"Unknown primary expression", expr.location};
	}
}