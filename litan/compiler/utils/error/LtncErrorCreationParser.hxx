#pragma once
#include "LtncError.hxx"

namespace ltn::c {
	namespace error {
		Error expectedExpression(const DebugInfo & debugInfo);
		Error expectedStatement(const DebugInfo & debugInfo);
		Error expectedDeclaration(const DebugInfo & debugInfo);

		Error expectedSemicolon(const DebugInfo & debugInfo);

		Error expectedParenL(const DebugInfo & debugInfo);
		Error expectedParenR(const DebugInfo & debugInfo);
		Error expectedBraceL(const DebugInfo & debugInfo);
		Error expectedBraceR(const DebugInfo & debugInfo);
		Error expectedChevronL(const DebugInfo & debugInfo);
		Error expectedChevronR(const DebugInfo & debugInfo);

		Error expectedComma(const DebugInfo & debugInfo);
		Error expectedEqual(const DebugInfo & debugInfo);

		Error expectedIdentifier(const DebugInfo & debugInfo);

		Error unnamedFunction(const DebugInfo & debugInfo);
		Error unnamedNamespace(const DebugInfo & debugInfo);
		Error unnamedStruct(const DebugInfo & debugInfo);
		Error unnamedType(const DebugInfo & debugInfo);
		Error unnamedVariable(const DebugInfo & debugInfo);
		Error unnamedParameter(const DebugInfo & debugInfo);

		Error malformedFor(const DebugInfo & debugInfo);
		Error malformedWhile(const DebugInfo & debugInfo);
		Error malformedRepeat(const DebugInfo & debugInfo);

		Error missingCondition(const DebugInfo & debugInfo);
		Error missingIfBranch(const DebugInfo & debugInfo);
		Error missingReturnType(const DebugInfo & debugInfo);

		Error unopenedAsm(const DebugInfo & debugInfo);
		Error unclosedAsm(const DebugInfo & debugInfo);

		Error unopenedParameterList(const DebugInfo & debugInfo);
		Error unclosedParameterList(const DebugInfo & debugInfo);
	}
}