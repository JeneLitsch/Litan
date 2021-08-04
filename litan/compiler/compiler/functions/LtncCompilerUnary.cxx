#include "LtncCompilerFunctions.hxx"

ltnc::ExprInfo ltnc::compile::unary(CompilerPack & compPkg, const ExprUnary & expr) {
	CodeBuffer code = compPkg.codeBuffer();
	ExprInfo exprInfo = expression(compPkg, *expr.r);
	code << exprInfo.code;
	switch (expr.type)	{
	
	case TokenType::MINUS: {
		if(exprInfo.typeId == TypeId(TInt)){
			code << AssemblyCode("mnsi");
			return ExprInfo(exprInfo.typeId, code);
		}
		if(exprInfo.typeId == TypeId(TFloat)) {
			code << AssemblyCode("mnsf");
			return ExprInfo(exprInfo.typeId, code);
		}
		throw error::incompatibleOperator(exprInfo.typeId, "-", expr.debugInfo);
	}


	case TokenType::LOG_NOT: {
		ExprInfo exprInfo = expression(compPkg, *expr.r);
		if(exprInfo.typeId == TypeId(TInt)){
			code << AssemblyCode("lognot");
			return ExprInfo(exprInfo.typeId, code);
		}
		throw error::incompatibleOperator(exprInfo.typeId, "!", expr.debugInfo);
	}


	case TokenType::BIT_NOT: {
		ExprInfo exprInfo = expression(compPkg, *expr.r);
		if(exprInfo.typeId == TypeId(TInt)){
			code << AssemblyCode("bitnot");
			return ExprInfo(exprInfo.typeId, code);
		}
		throw error::incompatibleOperator(exprInfo.typeId, "~", expr.debugInfo);
	}


	case TokenType::COPY: {
		ExprInfo exprInfo = expression(compPkg, *expr.r);
		if(exprInfo.typeId == TypeId(TInt)){
			throw std::runtime_error("Cannot copy int");
		}
		if(exprInfo.typeId == TypeId(TFloat)) {
			throw std::runtime_error("Cannot copy flt");
		}
		code << AssemblyCode("heap::copy");
		return ExprInfo(exprInfo.typeId, code);
	}


	default:
		throw error::invalidUnaryExpression(expr.debugInfo);
	}
}