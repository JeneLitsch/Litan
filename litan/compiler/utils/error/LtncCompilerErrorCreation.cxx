#include "LtncCompilerErrorCreation.hxx"
#include <unordered_map>

namespace ltnc {
	CompilerError error::invalidToken(const DebugInfo & debugInfo, const std::string & token) {
		return CompilerError(ErrorCode::INVALID_TOKEN, "Invalid Token: " + token, debugInfo);
	}


	CompilerError error::expectedExpression(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_EXPRESSION, "Expected expression", debugInfo);
	}

	CompilerError error::expectedStatement(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_STATEMENT, "Expected expression", debugInfo);
	}
	
	CompilerError error::expectedDeclaration(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_DECLARATION, "Expected declaration", debugInfo);
	}

	CompilerError error::expectedSemicolon(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_SEMICOLON, "Expected ;", debugInfo);
	}

	CompilerError error::expectedParenL(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_PAREN_L, "Expected (", debugInfo);
	}

	CompilerError error::expectedParenR(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_PAREN_R, "Expected )", debugInfo);
	}

	CompilerError error::expectedBraceL(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_BRACE_L, "Expected {", debugInfo);
	}

	CompilerError error::expectedBraceR(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_BRACE_R, "Expected }", debugInfo);
	}

	CompilerError error::expectedComma(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_COMMA, "Expected ,", debugInfo);
	}

	CompilerError error::expectedEqual(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_EQUAL, "Expected =", debugInfo);
	}

	CompilerError error::expectedIdentifier(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::EXPECTED_IDENTIFIER, "Expected identifier", debugInfo);
	}



	CompilerError error::unnamedFunction(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNNAMED_FUNCTION, "Expected function name", debugInfo);
	}

	CompilerError error::unnamedNamespace(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNNAMED_NAMESPACE, "Expected namespace name", debugInfo);
	}

	CompilerError error::unnamedStruct(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNNAMED_STRUCT, "Expected struct name", debugInfo);
	}

	CompilerError error::unnamedType(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNNAMED_TYPE, "Expected type name", debugInfo);
	}

	CompilerError error::unnamedVariable(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNNAMED_VARIABLE, "Expected type name", debugInfo);
	}

	CompilerError error::unnamedParameter(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNNAMED_PARAMETER, "Expected parameter name", debugInfo);
	}



	CompilerError error::malformedFor(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::MALFORMED_FOR, "Malformed for loop", debugInfo);
	}

	CompilerError error::malformedWhile(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::MALFORMED_WHILE, "Malformed while loop", debugInfo);
	}

	CompilerError error::malformedRepeat(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::MALFORMED_REPEAT, "Malformed repeat loop", debugInfo);
	}



	CompilerError error::missingCondition(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::MISSING_CONDITION, "Expected condition", debugInfo);
	}

	CompilerError error::missingIfBranch(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::MISSING_IF_BRANCH, "Expected statement after if", debugInfo);
	}

	CompilerError error::missingReturnType(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::MISSING_RETURN_TYPE, "Missing return type" , debugInfo);
	}



	CompilerError error::unopenedAsm(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNOPENED_ASM_BLOCK, "Expected { before assembly block", debugInfo);
	}

	CompilerError error::unclosedAsm(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNCLOSED_ASM_BLOCK, "Expected } after assembly block", debugInfo);
	}

	CompilerError error::unopenedParameterList(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNOPENED_PARAMETER_LIST, "Missing parameter list. Expected (", debugInfo);
	}

	CompilerError error::unclosedParameterList(const DebugInfo & debugInfo) {
		return CompilerError(ErrorCode::UNCLOSED_PARAMETER_LIST, "Unclosed parameter list. Expected )", debugInfo);
	}
}


