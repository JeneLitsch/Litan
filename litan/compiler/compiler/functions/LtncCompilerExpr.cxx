#include "LtncCompilerFunctions.hxx"

ltn::c::ExprInfo ltn::c::compile::expression(CompilerPack & compPkg, const Expr & expr) {
	if(auto expr_ = dynamic_cast<const ExprLiteral *>(&expr)) {
		return literal(compPkg, *expr_);
	}
	if(auto expr_ = dynamic_cast<const ExprVar*>(&expr)) {
		return var(compPkg, *expr_, {});
	}
	if(auto expr_ = dynamic_cast<const ExprBinary*>(&expr)) {
		return binaryExpr(compPkg, *expr_);
	}
	if(auto expr_ = dynamic_cast<const ExprCall*>(&expr)) {
		return call(compPkg, *expr_);
	}
	if(auto expr_ = dynamic_cast<const ExprUnary*>(&expr)) {
		return unary(compPkg, *expr_);
	}
	throw error::invalidExpression(expr.debugInfo);
}

