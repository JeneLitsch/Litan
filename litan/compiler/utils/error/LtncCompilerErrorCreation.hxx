#pragma once
#include "LtncCompilerError.hxx"

namespace ltnc {
	namespace error {
		CompilerError expectedExpression(const TokenDebugInfo & debugInfo);
		CompilerError expectedStatement(const TokenDebugInfo & debugInfo);
		CompilerError expectedDeclaration(const TokenDebugInfo & debugInfo);

		CompilerError expectedSemicolon(const TokenDebugInfo & debugInfo);

		CompilerError expectedParenL(const TokenDebugInfo & debugInfo);
		CompilerError expectedParenR(const TokenDebugInfo & debugInfo);
		CompilerError expectedBraceL(const TokenDebugInfo & debugInfo);
		CompilerError expectedBraceR(const TokenDebugInfo & debugInfo);

		CompilerError expectedComma(const TokenDebugInfo & debugInfo);
		CompilerError expectedEqual(const TokenDebugInfo & debugInfo);

		CompilerError expectedIdentifier(const TokenDebugInfo & debugInfo);

		CompilerError unnamedFunction(const TokenDebugInfo & debugInfo);
		CompilerError unnamedNamespace(const TokenDebugInfo & debugInfo);
		CompilerError unnamedStruct(const TokenDebugInfo & debugInfo);
		CompilerError unnamedType(const TokenDebugInfo & debugInfo);
		CompilerError unnamedVariable(const TokenDebugInfo & debugInfo);
		CompilerError unnamedParameter(const TokenDebugInfo & debugInfo);

		CompilerError malformedFor(const TokenDebugInfo & debugInfo);
		CompilerError malformedWhile(const TokenDebugInfo & debugInfo);
		CompilerError malformedRepeat(const TokenDebugInfo & debugInfo);

		CompilerError missingCondition(const TokenDebugInfo & debugInfo);
		CompilerError missingIfBranch(const TokenDebugInfo & debugInfo);
		CompilerError missingReturnType(const TokenDebugInfo & debugInfo);

		CompilerError unopenedAsm(const TokenDebugInfo & debugInfo);
		CompilerError unclosedAsm(const TokenDebugInfo & debugInfo);

		CompilerError unopenedParameterList(const TokenDebugInfo & debugInfo);
		CompilerError unclosedParameterList(const TokenDebugInfo & debugInfo);
	}
}