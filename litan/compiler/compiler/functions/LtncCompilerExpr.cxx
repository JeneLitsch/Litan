#include "LtncCompilerFunctions.hxx"

ltnc::ExprInfo ltnc::compile::expression(CompilerPack & compPkg, const Expr & expr) {
	if(auto expr_ = dynamic_cast<const ExprIntLiteral *>(&expr)) {
		return intLiteral(compPkg, *expr_);
	}
	if(auto expr_ = dynamic_cast<const ExprFltLiteral *>(&expr)) {
		return floatLiteral(compPkg, *expr_);
	}
	if(auto expr_ = dynamic_cast<const ExprStrLiteral*>(&expr)) {
		return stringLiteral(compPkg, *expr_);
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
	if(auto expr_ = dynamic_cast<const ExprNul*>(&expr)) {
		return nul();
	}
	if(auto expr_ = dynamic_cast<const ExprBool*>(&expr)) {
		return boolLiteral(*expr_);
	}
	throw error::invalidExpression(expr.debugInfo);
}

