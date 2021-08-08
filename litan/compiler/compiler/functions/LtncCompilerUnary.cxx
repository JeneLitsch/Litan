#include "LtncCompilerFunctions.hxx"

ltnc::ExprInfo ltnc::compile::unary(CompilerPack & compPkg, const ExprUnary & expr) {
	CodeBuffer code = compPkg.codeBuffer();
	ExprInfo exprInfo = expression(compPkg, *expr.r);
	switch (expr.type)	{
	
	case TokenType::MINUS: {
		if(exprInfo.typeId == TypeId(TInt)){
			if(exprInfo.constValue) {
				code << Inst::newi(-std::get<std::int64_t>(exprInfo.constValue->value));
				return ExprInfo(exprInfo.typeId, code);
			}
			else {
				code << exprInfo.code;
				code << AssemblyCode("mnsi");
				return ExprInfo(exprInfo.typeId, code);
			}
		}
		if(exprInfo.typeId == TypeId(TFloat)) {
			if(exprInfo.constValue) {
				code << Inst::newf(-std::get<double>(exprInfo.constValue->value));
				return ExprInfo(exprInfo.typeId, code);
			}
			else {
				code << exprInfo.code;
				code << AssemblyCode("mnsf");
				return ExprInfo(exprInfo.typeId, code);
			}
		}
		throw error::incompatibleOperator(exprInfo.typeId, "-", expr.debugInfo);
	}


	case TokenType::LOG_NOT: {
		ExprInfo exprInfo = expression(compPkg, *expr.r);
		if(	exprInfo.typeId == TypeId(TInt) ||
			exprInfo.typeId == TypeId(TBool)) {
			code << exprInfo.code;
			code << AssemblyCode("lognot");
			return ExprInfo(TBool, code);
		}
		throw error::incompatibleOperator(exprInfo.typeId, "!", expr.debugInfo);
	}


	case TokenType::BIT_NOT: {
		ExprInfo exprInfo = expression(compPkg, *expr.r);
		if(exprInfo.typeId == TypeId(TInt)){
			code << exprInfo.code;
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
		code << exprInfo.code;
		code << AssemblyCode("heap::copy");
		return ExprInfo(exprInfo.typeId, code);
	}


	default:
		throw error::invalidUnaryExpression(expr.debugInfo);
	}
}