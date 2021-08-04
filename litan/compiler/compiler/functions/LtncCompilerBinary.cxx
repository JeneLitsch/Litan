#include "LtncCompilerFunctions.hxx"

#include "LtncAddEvaluator.hxx"
#include "LtncSubEvaluator.hxx"
#include "LtncMltEvaluator.hxx"
#include "LtncDivEvaluator.hxx"
#include "LtncModEvaluator.hxx"

std::string getSuffux(const ltnc::TypeId & typeId) {
	if(typeId == TInt) {
		return "i";
	}
	if(typeId == TFloat) {
		return "f";
	}
	throw std::runtime_error("Invalid Type for operation");
}

ltnc::ExprInfo buildBinary(
	ltnc::CompilerPack & compPkg,
	const ltnc::ExprBinary & expr,
	const std::string & command,
	const ltnc::Evaluator * eval = nullptr) {
	

	// left and right
	ltnc::ExprInfo l = ltnc::compile::expression(compPkg, *expr.l);
	ltnc::ExprInfo r = ltnc::compile::expression(compPkg, *expr.r);
	// mismatch
	if(l.typeId != r.typeId) {
		throw ltnc::error::incompatibleTypes(expr.debugInfo, l.typeId, r.typeId);
	}
	// i or f for int or float
	std::string suffix = getSuffux(l.typeId);

	// try constant folding
	if(eval && compPkg.getSettings().getOptimizationLevel()) {		
		if(auto optimized = eval->optimize(l, r)) {
			return *optimized;
		}
	}

	ltnc::CodeBuffer code(compPkg.getSettings().areCommentsActive());
	code << l.code;
	code << r.code;
	code << ltnc::AssemblyCode(command + suffix);
	
	return ltnc::ExprInfo(l.typeId, code);
}

ltnc::ExprInfo overrideType(
	const ltnc::ExprInfo & exprInfo,
	const ltnc::TypeId & typeId) {
	if(exprInfo.constValue) {
		return ltnc::ExprInfo(typeId, exprInfo.code, *exprInfo.constValue);
	}
	return ltnc::ExprInfo(typeId, exprInfo.code);
}

ltnc::ExprInfo ltnc::compile::binaryExpr(CompilerPack & compPkg, const ExprBinary & expr) {
	static const AddEvaluator addEvaluator;
	static const SubEvaluator subEvaluator;
	static const MltEvaluator mltEvaluator;
	static const DivEvaluator divEvaluator;
	static const ModEvaluator modEvaluator;
	
	switch (expr.type)	{
	// comparision operator
	case TokenType::EQUAL:			return overrideType(buildBinary(compPkg, expr, "eql"), TBool);
	case TokenType::UNEQUAL: 		return overrideType(buildBinary(compPkg, expr, "uneql"), TBool);
	case TokenType::SMALLER: 		return overrideType(buildBinary(compPkg, expr, "sml"), TBool);
	case TokenType::SMALLEREQUAL: 	return overrideType(buildBinary(compPkg, expr, "smleql"), TBool);
	case TokenType::BIGGER: 		return overrideType(buildBinary(compPkg, expr, "bgr"), TBool);
	case TokenType::BIGGEREQUAL: 	return overrideType(buildBinary(compPkg, expr, "bgreql"), TBool);

	// arithmetic binary operators 
	case TokenType::PLUS: 			return buildBinary(compPkg, expr, "add", &addEvaluator);
	case TokenType::MINUS: 			return buildBinary(compPkg, expr, "sub", &subEvaluator);
	case TokenType::STAR: 			return buildBinary(compPkg, expr, "mlt", &mltEvaluator);
	case TokenType::SLASH: 			return buildBinary(compPkg, expr, "div", &divEvaluator);
	case TokenType::MOD: 			return buildBinary(compPkg, expr, "mod", &modEvaluator);

	// error
	default: 						throw error::invalidBinaryExpression(expr.debugInfo);
	}
}
