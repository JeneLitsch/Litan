#include "LtncErrorCreationCompiler.hxx"
#include <sstream>

ltnc::Error ltnc::error::incompatibleTypes(
	const DebugInfo & debugInfo,
	const TypeId & from,
	const TypeId & to) {
	std::stringstream ss;
	ss 	<< "Incompatible types: "
		<< from
		<< " -> "
		<< to;
	return Error(ErrorCode::INCOMPATIBLE_TYPES, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::noMatchingFunction(
	const DebugInfo & debugInfo,
	const FunctionSignature & fxSignature) {
	std::stringstream ss;
	ss	<< "No matching function: "
		<< fxSignature;
	return Error(ErrorCode::NO_MATCHING_FUNCTION, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::voidParameter(
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Void parameter is not allowed.";
	return Error(ErrorCode::VOID_PARAMETER, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::voidVariable(
	const DebugInfo & debugInfo,
	const VarId & varId){
	std::stringstream ss;
	ss	<< "Variable " << varId << " has type Void. " 
		<< "Void is not allowed here. ";
	return Error(ErrorCode::VOID_VARIABLE, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::lowerBoundNotInt(
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Lower bound of for loop needs to be an Int.";
	return Error(ErrorCode::LOWER_BOUND_NOT_INT, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::upperBoundNotInt(
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Upper bound of for loop needs to be an Int.";
	return Error(ErrorCode::UPPER_BOUND_NOT_INT, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::repeatCountNotInt(
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Repeat count needs to be an Int.";
	return Error(ErrorCode::REPEAT_COUNT_NOT_INT, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::unmatchingReturnType(
	const TypeId & returnType,
	const TypeId & exprType,
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Return type do not match: "
		<< exprType
		<< " -> "
		<< returnType;
	return Error(ErrorCode::UNMATCHING_RETURN_TYPE, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::incompatibleOperator(
	const TypeId & typeId,
	const std::string & op,
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Operator "
		<< op
		<< " is not available for type "
		<< typeId;
	return Error(ErrorCode::INCOMPATIBLE_OPERATOR, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::notAMember(
	const ltnc::VarId & member,
	const ltnc::TypeId & typeId,
	const ltnc::DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< member 
		<< " is not a member of "
		<< typeId;
	return Error(ErrorCode::NOT_A_MEMBER, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::undefinedVariable(
	const ltnc::VarId & member,
	const ltnc::DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Variable " 
		<< member
		<< " is not defined";
	return Error(ErrorCode::UNDEFINED_VARIABLE, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::invalidStatement(
	const DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Invalid statement";
	return Error(ErrorCode::INVALID_STATEMENT, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::invalidExpression(
	const DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Invalid expression";
	return Error(ErrorCode::INVALID_EXPRESSION, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::invalidBinaryExpression(
	const DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Invalid binary expression";
	return Error(ErrorCode::INVALID_BINARY_EXPRESSION, ss.str(), debugInfo);
}

ltnc::Error ltnc::error::invalidUnaryExpression(
	const DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Invalid unary expression";
	return Error(ErrorCode::INVALID_UNARY_EXPRESSION, ss.str(), debugInfo);
}