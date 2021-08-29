#include "LtncCompilerFunctions.hxx"

#include "LtncAddEvaluator.hxx"
#include "LtncSubEvaluator.hxx"
#include "LtncMltEvaluator.hxx"
#include "LtncDivEvaluator.hxx"
#include "LtncModEvaluator.hxx"

#include <functional>

std::string useSuffux(const ltn::c::TypeId & typeId) {
	if(typeId == TInt) return "i";
	if(typeId == TBool) return "i";
	if(typeId == TFloat) return "f";
	throw std::runtime_error("Invalid Type for operation");
}

std::string ingoreSuffix(const ltn::c::TypeId & typeId) {
	if(typeId == TInt) return "";
	if(typeId == TBool) return "";
	if(typeId == TFloat) return "";
	throw std::runtime_error("Invalid Type for operation");
}

std::optional<ltn::c::TypeId> matchTypes(
	const ltn::c::TypeId & typeL,
	const ltn::c::TypeId & typeR) {
	
	if(typeL == typeR) return typeL;
	if(typeL == TInt && typeR == TBool) return TInt;
	if(typeL == TBool && typeR == TInt) return TInt;
	return {};
}

ltn::c::ExprInfo buildBinary(
	ltn::c::CompilerPack & compPkg,
	const ltn::c::ExprBinary & expr,
	const std::string & command,
	const std::function<std::string(const ltn::c::TypeId & typeId)> & getSuffix,
	const ltn::c::Evaluator * eval = nullptr) {
	
	// left and right
	ltn::c::ExprInfo l = ltn::c::compile::expression(compPkg, *expr.l);
	ltn::c::ExprInfo r = ltn::c::compile::expression(compPkg, *expr.r);
	// mismatch
	std::optional<ltn::c::TypeId> type = matchTypes(l.typeId, r.typeId);
	if(!type) {
		throw ltn::c::error::incompatibleTypes(expr.debugInfo, l.typeId, r.typeId);
	}
	// i or f for int or float
	std::string suffix = getSuffix(*type);

	// try constant folding
	if(eval && compPkg.getSettings().getOptimizationLevel()) {		
		if(auto optimized = eval->optimize(l, r)) {
			return *optimized;
		}
	}

	ltn::c::CodeBuffer code(compPkg.getSettings().areCommentsActive());
	code << l.code;
	code << r.code;
	code << ltn::c::AssemblyCode(command + suffix);
	
	return ltn::c::ExprInfo(*type, code);
}

ltn::c::ExprInfo overrideType(
	const ltn::c::ExprInfo & exprInfo,
	const ltn::c::TypeId & typeId) {
	if(exprInfo.constValue) {
		return ltn::c::ExprInfo(typeId, exprInfo.code, *exprInfo.constValue);
	}
	return ltn::c::ExprInfo(typeId, exprInfo.code);
}

ltn::c::ExprInfo ltn::c::compile::binaryExpr(CompilerPack & compPkg, const ExprBinary & expr) {
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
