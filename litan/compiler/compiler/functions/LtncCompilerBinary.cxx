#include "LtncCompilerFunctions.hxx"

#include "LtncAddEvaluator.hxx"
#include "LtncSubEvaluator.hxx"
#include "LtncMltEvaluator.hxx"
#include "LtncDivEvaluator.hxx"
#include "LtncModEvaluator.hxx"

#include <functional>

std::string useSuffux(const ltnc::TypeId & typeId) {
	if(typeId == TInt) return "i";
	if(typeId == TBool) return "i";
	if(typeId == TFloat) return "f";
	throw std::runtime_error("Invalid Type for operation");
}

std::string ingoreSuffix(const ltnc::TypeId & typeId) {
	if(typeId == TInt) return "";
	if(typeId == TBool) return "";
	if(typeId == TFloat) return "";
	throw std::runtime_error("Invalid Type for operation");
}

std::optional<ltnc::TypeId> matchTypes(
	const ltnc::TypeId & typeL,
	const ltnc::TypeId & typeR) {
	
	if(typeL == typeR) return typeL;
	if(typeL == TInt && typeR == TBool) return TInt;
	if(typeL == TBool && typeR == TInt) return TInt;
	return {};
}

ltnc::ExprInfo buildBinary(
	ltnc::CompilerPack & compPkg,
	const ltnc::ExprBinary & expr,
	const std::string & command,
	const std::function<std::string(const ltnc::TypeId & typeId)> & getSuffix,
	const ltnc::Evaluator * eval = nullptr) {
	
	// left and right
	ltnc::ExprInfo l = ltnc::compile::expression(compPkg, *expr.l);
	ltnc::ExprInfo r = ltnc::compile::expression(compPkg, *expr.r);
	// mismatch
	std::optional<ltnc::TypeId> type = matchTypes(l.typeId, r.typeId);
	if(!type) {
		throw ltnc::error::incompatibleTypes(expr.debugInfo, l.typeId, r.typeId);
	}
	// i or f for int or float
	std::string suffix = getSuffix(*type);

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
	
	return ltnc::ExprInfo(*type, code);
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
	// static const AddEvaluator addEvaluator;
	// static const SubEvaluator subEvaluator;
	// static const MltEvaluator mltEvaluator;
	// static const DivEvaluator divEvaluator;
	// static const ModEvaluator modEvaluator;
	
	switch (expr.type)	{
	// comparision operator
	case TokenType::LOG_AND:		return overrideType(buildBinary(compPkg, expr, "logand", ingoreSuffix), TBool);
	case TokenType::LOG_OR:			return overrideType(buildBinary(compPkg, expr, "logor", ingoreSuffix), TBool);

	case TokenType::EQUAL:			return overrideType(buildBinary(compPkg, expr, "eql", useSuffux), TBool);
	case TokenType::UNEQUAL: 		return overrideType(buildBinary(compPkg, expr, "uneql", useSuffux), TBool);

	case TokenType::SMALLER: 		return overrideType(buildBinary(compPkg, expr, "sml", useSuffux), TBool);
	case TokenType::SMALLEREQUAL: 	return overrideType(buildBinary(compPkg, expr, "smleql", useSuffux), TBool);
	case TokenType::BIGGER: 		return overrideType(buildBinary(compPkg, expr, "bgr", useSuffux), TBool);
	case TokenType::BIGGEREQUAL: 	return overrideType(buildBinary(compPkg, expr, "bgreql", useSuffux), TBool);

	case TokenType::SPACESHIP:		return overrideType(buildBinary(compPkg, expr, "spsh", useSuffux), TInt);

	// arithmetic binary operators 
	case TokenType::PLUS: 			return buildBinary(compPkg, expr, "add", useSuffux);
	case TokenType::MINUS: 			return buildBinary(compPkg, expr, "sub", useSuffux);
	case TokenType::STAR: 			return buildBinary(compPkg, expr, "mlt", useSuffux);
	case TokenType::SLASH: 			return buildBinary(compPkg, expr, "div", useSuffux);
	case TokenType::MOD: 			return buildBinary(compPkg, expr, "mod", useSuffux);
	case TokenType::POWER: 			return buildBinary(compPkg, expr, "pow", useSuffux);

	// error
	default: 						throw error::invalidBinaryExpression(expr.debugInfo);
	}
}
