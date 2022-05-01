#include "compile.hxx"

namespace ltn::c::compile {
	// compiles any expression
	ExprCode expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		if(auto binary = as<ast::Binary>(expr)) {
			return compile::binary(*binary, info, scope);
		}
		if(auto unary = as<ast::Unary>(expr)) {
			return compile::unary(*unary, info, scope);
		}
		if(auto expr_ = as<ast::Integer>(expr)) {
			return compile::integer(*expr_);
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
		if(auto ternary = as<ast::Ternary>(expr)) {
			return compile::ternary(*ternary, info, scope);
		} 
		if(auto sw1tch = as<ast::ExprSwitch>(expr)) {
			return compile::expr_switch(*sw1tch, info, scope);
		} 
		if(auto invoke = as<ast::Invokation>(expr)) {
			return compile::invokation(*invoke, info, scope);
		} 
		throw CompilerError{"Unknown Expression"};
	}



	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw CompilerError{
				"Cannot modify or reassign variable in const function",
				node.location};
		}
	}
}