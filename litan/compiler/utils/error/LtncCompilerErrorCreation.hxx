#pragma once
#include "LtncCompilerError.hxx"

namespace ltnc {
	namespace error {
		CompilerError invalidToken(const DebugInfo & debugInfo, const std::string & token);


		CompilerError expectedExpression(const DebugInfo & debugInfo);
		CompilerError expectedStatement(const DebugInfo & debugInfo);
		CompilerError expectedDeclaration(const DebugInfo & debugInfo);

		CompilerError expectedSemicolon(const DebugInfo & debugInfo);

		CompilerError expectedParenL(const DebugInfo & debugInfo);
		CompilerError expectedParenR(const DebugInfo & debugInfo);
		CompilerError expectedBraceL(const DebugInfo & debugInfo);
		CompilerError expectedBraceR(const DebugInfo & debugInfo);

		CompilerError expectedComma(const DebugInfo & debugInfo);
		CompilerError expectedEqual(const DebugInfo & debugInfo);

		CompilerError expectedIdentifier(const DebugInfo & debugInfo);

		CompilerError unnamedFunction(const DebugInfo & debugInfo);
		CompilerError unnamedNamespace(const DebugInfo & debugInfo);
		CompilerError unnamedStruct(const DebugInfo & debugInfo);
		CompilerError unnamedType(const DebugInfo & debugInfo);
		CompilerError unnamedVariable(const DebugInfo & debugInfo);
		CompilerError unnamedParameter(const DebugInfo & debugInfo);

		CompilerError malformedFor(const DebugInfo & debugInfo);
		CompilerError malformedWhile(const DebugInfo & debugInfo);
		CompilerError malformedRepeat(const DebugInfo & debugInfo);

		CompilerError missingCondition(const DebugInfo & debugInfo);
		CompilerError missingIfBranch(const DebugInfo & debugInfo);
		CompilerError missingReturnType(const DebugInfo & debugInfo);

		CompilerError unopenedAsm(const DebugInfo & debugInfo);
		CompilerError unclosedAsm(const DebugInfo & debugInfo);

		CompilerError unopenedParameterList(const DebugInfo & debugInfo);
		CompilerError unclosedParameterList(const DebugInfo & debugInfo);
	}
}