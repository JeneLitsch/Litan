#include "compile.hxx"

namespace ltn::c::compile {
	namespace {
		using MT = ast::Modify::Type;
		
		// =
		ExprCode assign(
			const ast::Assign & expr,
			CompilerInfo & info,
			Scope & scope) {
			const auto l = compile::assignable(*expr.l, info, scope);
			const auto r = compile::expression(*expr.r, info, scope);
			std::stringstream ss;
			ss << r.code;
			ss << l.code;
			ss << inst::null;
			return ExprCode{ss.str() };
		}

		// += -= *= /= %=
		ExprCode modify(
			const ast::Modify & expr,
			CompilerInfo & info,
			Scope & scope) {
			const auto lW = compile::assignable(*expr.l, info, scope);
			const auto lR = compile::expression(*expr.l, info, scope);
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
			ss << lR.code;
			ss << r.code;
			ss << op;
			ss << lW.code;			
			ss << inst::null;
			return ExprCode{ss.str() };
		}
	}

	ExprCode ternary(const ast::Ternary & expr, CompilerInfo & info, Scope & scope) {
		const auto jumpmark = make_jump_id("TERNARY", info);
		const auto jumpmark_else = jumpmark + "_ELSE"; 
		const auto jumpmark_end = jumpmark + "_END"; 
		std::ostringstream ss;

		ss << expression(*expr.condition, info, scope).code;
		ss << inst::ifelse(jumpmark_else);

		ss << expression(*expr.if_expr, info, scope).code;
		ss << inst::jump(jumpmark_end);

		ss << inst::jumpmark(jumpmark_else);
		ss << expression(*expr.else_expr, info, scope).code;
		ss << inst::jump(jumpmark_end);

		ss << inst::jumpmark(jumpmark_end);

		return {ss.str()};
	}


	ExprCode elvis(const ast::Elvis & expr, CompilerInfo & info, Scope & scope) {
		const auto jumpmark = make_jump_id("ELVIS", info);
		const auto jumpmark_else = jumpmark + "_ELSE"; 
		const auto jumpmark_end = jumpmark + "_END"; 
		std::ostringstream ss;
		ss << expression(*expr.if_expr, info, scope).code;
		ss << inst::duplicate;
		ss << inst::ifelse(jumpmark_else);
		ss << inst::jump(jumpmark_end);

		ss << inst::jumpmark(jumpmark_else);
		ss << inst::scrap;
		ss << expression(*expr.else_expr, info, scope).code;
		
		ss << inst::jumpmark(jumpmark_end);
		return {ss.str()};
	}


	ExprCode nullco(const ast::Nullco & expr, CompilerInfo & info, Scope & scope) {
		const auto jumpmark = make_jump_id("NULLCO", info);
		const auto jumpmark_else = jumpmark + "_ELSE"; 
		const auto jumpmark_end = jumpmark + "_END"; 
		std::ostringstream ss;
		ss << expression(*expr.if_expr, info, scope).code;
		ss << inst::duplicate;
		ss << inst::null;
		ss << inst::ueql;
		ss << inst::ifelse(jumpmark_else);
		ss << inst::jump(jumpmark_end);

		ss << inst::jumpmark(jumpmark_else);
		ss << inst::scrap;
		ss << expression(*expr.else_expr, info, scope).code;
		
		ss << inst::jumpmark(jumpmark_end);
		return {ss.str()};
	}




	// compiles any expression
	ExprCode expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		if(auto binary = as<ast::Binary>(expr)) {
			return compile::binary(*binary, info, scope);
		}
		if(auto unary = as<ast::Unary>(expr)) {
			return compile::unary(*unary, info, scope);
		}
		if(auto primary = as<ast::Primary>(expr)) {
			return compile::primary(*primary, info, scope);
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
		if(auto elvis = as<ast::Elvis>(expr)) {
			return compile::elvis(*elvis, info, scope);
		} 
		if(auto nullco = as<ast::Nullco>(expr)) {
			return compile::nullco(*nullco, info, scope);
		} 

		throw CompilerError{"Unknown Expression"};
	}
}