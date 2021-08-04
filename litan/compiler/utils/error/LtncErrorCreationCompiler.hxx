#pragma once
#include "LtncError.hxx"

namespace ltnc {
	namespace error {
		Error incompatibleTypes(
			const DebugInfo & debugInfo,
			const TypeId & from,
			const TypeId & to);

		Error noMatchingFunction(
			const DebugInfo & debugInfo,
			const FunctionSignature & fxSignature);
	
		Error voidParameter(
			const DebugInfo & debugInfo);

		Error voidVariable(
			const DebugInfo & debugInfo,
			const VarId & varId);

		Error lowerBoundNotInt(
			const DebugInfo & debugInfo);

		Error upperBoundNotInt(
			const DebugInfo & debugInfo);

		Error repeatCountNotInt(
			const DebugInfo & debugInfo);

		Error unmatchingReturnType(
			const TypeId & returnType,
			const TypeId & exprType,
			const DebugInfo & debugInfo);

		Error incompatibleOperator(
			const TypeId & typeId,
			const std::string & op,
			const DebugInfo & debugInfo);

		Error notAMember(
			const VarId & member,
			const TypeId & typeId,
			const DebugInfo & debugInfo);

		Error undefinedVariable(
			const VarId & member,
			const DebugInfo & debugInfo);

		Error invalidStatement(
			const DebugInfo & debugInfo);

		Error invalidExpression(
			const DebugInfo & debugInfo);

		Error invalidBinaryExpression(
			const DebugInfo & debugInfo);

		Error invalidUnaryExpression(
			const DebugInfo & debugInfo);
	}
}