#include "compile.hxx"

namespace ltn::c::compile {
	namespace {
		using MT = ast::Modify::Type;



		// =
		ExprCode assign(
			const ast::Assign & expr,
			CompilerInfo & info,
			Scope & scope) {
			guard_const(expr, scope);
			const auto l = compile::assignable(*expr.l, info, scope);
			const auto r = compile::expression(*expr.r, info, scope);
			std::stringstream ss;
			ss << r.code;
			ss << inst::duplicate;
			ss << l.code;
			return ExprCode{ss.str() };
		}



		// += -= *= /= %=
		ExprCode modify(
			const ast::Modify & expr,
			CompilerInfo & info,
			Scope & scope) {
			guard_const(expr, scope);
			const auto l_write = compile::assignable(*expr.l, info, scope);
			const auto l_read = compile::expression(*expr.l, info, scope);
			const auto r = compile::expression(*expr.r, info, scope);
			const auto op = [&] {
				switch (expr.type) {
				case MT::ADD: return inst::add;
				case MT::SUB: return inst::sub;
				case MT::MLT: return inst::mlt;
				case MT::DIV: return inst::div;
				case MT::MOD: return inst::mod;
				case MT::SHIFT_L: return inst::shift_l;
				case MT::SHIFT_R: return inst::shift_r;
				}
				throw CompilerError{
					"Unknow modify operator",
					expr.location};
			}();
			std::stringstream ss;
			ss << l_read.code;
			ss << r.code;
			ss << op;
			ss << inst::duplicate;
			ss << l_write.code;			
			return ExprCode{ss.str() };
		}
	}



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
		if(auto assign = as<ast::Assign>(expr)) {
			return compile::assign(*assign, info, scope);
		}
		if(auto modify = as<ast::Modify>(expr)) {
			return compile::modify(*modify, info, scope);
		}
		if(auto ternary = as<ast::Ternary>(expr)) {
			return compile::ternary(*ternary, info, scope);
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