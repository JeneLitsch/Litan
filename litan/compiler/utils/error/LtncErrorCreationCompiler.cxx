#include "LtncErrorCreationCompiler.hxx"
#include <sstream>

ltn::c::Error ltn::c::error::incompatibleTypes(
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

ltn::c::Error ltn::c::error::noMatchingFunction(
	const DebugInfo & debugInfo,
	const FunctionSignature & fxSignature) {
	std::stringstream ss;
	ss	<< "No matching function: "
		<< fxSignature;
	return Error(ErrorCode::NO_MATCHING_FUNCTION, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::voidParameter(
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Void parameter is not allowed.";
	return Error(ErrorCode::VOID_PARAMETER, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::voidVariable(
	const DebugInfo & debugInfo,
	const VarId & varId){
	std::stringstream ss;
	ss	<< "Variable " << varId << " has type Void. " 
		<< "Void is not allowed here. ";
	return Error(ErrorCode::VOID_VARIABLE, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::lowerBoundNotInt(
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Lower bound of for loop needs to be an Int.";
	return Error(ErrorCode::LOWER_BOUND_NOT_INT, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::upperBoundNotInt(
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Upper bound of for loop needs to be an Int.";
	return Error(ErrorCode::UPPER_BOUND_NOT_INT, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::repeatCountNotInt(
	const DebugInfo & debugInfo){
	std::stringstream ss;
	ss	<< "Repeat count needs to be an Int.";
	return Error(ErrorCode::REPEAT_COUNT_NOT_INT, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::unmatchingReturnType(
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

ltn::c::Error ltn::c::error::incompatibleOperator(
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

ltn::c::Error ltn::c::error::notAMember(
	const ltn::c::VarId & member,
	const ltn::c::TypeId & typeId,
	const ltn::c::DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< member 
		<< " is not a member of "
		<< typeId;
	return Error(ErrorCode::NOT_A_MEMBER, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::undefinedVariable(
	const ltn::c::VarId & member,
	const ltn::c::DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Variable " 
		<< member
		<< " is not defined";
	return Error(ErrorCode::UNDEFINED_VARIABLE, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::invalidStatement(
	const DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Invalid statement";
	return Error(ErrorCode::INVALID_STATEMENT, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::invalidExpression(
	const DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Invalid expression";
	return Error(ErrorCode::INVALID_EXPRESSION, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::invalidBinaryExpression(
	const DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Invalid binary expression";
	return Error(ErrorCode::INVALID_BINARY_EXPRESSION, ss.str(), debugInfo);
}

ltn::c::Error ltn::c::error::invalidUnaryExpression(
	const DebugInfo & debugInfo) {
	std::stringstream ss;
	ss	<< "Invalid unary expression";
	return Error(ErrorCode::INVALID_UNARY_EXPRESSION, ss.str(), debugInfo);
}