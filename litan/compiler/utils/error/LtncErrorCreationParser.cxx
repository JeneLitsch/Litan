#include "LtncErrorCreationParser.hxx"

namespace ltn::c {
	Error error::expectedExpression(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_EXPRESSION, "Expected expression", debugInfo);
	}

	Error error::expectedStatement(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_STATEMENT, "Expected expression", debugInfo);
	}
	
	Error error::expectedDeclaration(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_DECLARATION, "Expected declaration", debugInfo);
	}

	Error error::expectedSemicolon(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_SEMICOLON, "Expected ;", debugInfo);
	}

	Error error::expectedParenL(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_PAREN_L, "Expected (", debugInfo);
	}

	Error error::expectedParenR(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_PAREN_R, "Expected )", debugInfo);
	}

	Error error::expectedBraceL(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_BRACE_L, "Expected {", debugInfo);
	}

	Error error::expectedBraceR(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_BRACE_R, "Expected }", debugInfo);
	}

	Error error::expectedChevronL(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_CHEVRON_L, "Expected <", debugInfo);
	}

	Error error::expectedChevronR(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_CHEVRON_R, "Expected >", debugInfo);
	}

	Error error::expectedComma(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_COMMA, "Expected ,", debugInfo);
	}

	Error error::expectedEqual(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_EQUAL, "Expected =", debugInfo);
	}

	Error error::expectedIdentifier(const DebugInfo & debugInfo) {
		return Error(ErrorCode::EXPECTED_IDENTIFIER, "Expected identifier", debugInfo);
	}



	Error error::unnamedFunction(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNNAMED_FUNCTION, "Expected function name", debugInfo);
	}

	Error error::unnamedNamespace(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNNAMED_NAMESPACE, "Expected namespace name", debugInfo);
	}

	Error error::unnamedStruct(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNNAMED_STRUCT, "Expected struct name", debugInfo);
	}

	Error error::unnamedType(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNNAMED_TYPE, "Expected type name", debugInfo);
	}

	Error error::unnamedVariable(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNNAMED_VARIABLE, "Expected type name", debugInfo);
	}

	Error error::unnamedParameter(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNNAMED_PARAMETER, "Expected parameter name", debugInfo);
	}



	Error error::malformedFor(const DebugInfo & debugInfo) {
		return Error(ErrorCode::MALFORMED_FOR, "Malformed for loop", debugInfo);
	}

	Error error::malformedWhile(const DebugInfo & debugInfo) {
		return Error(ErrorCode::MALFORMED_WHILE, "Malformed while loop", debugInfo);
	}

	Error error::malformedRepeat(const DebugInfo & debugInfo) {
		return Error(ErrorCode::MALFORMED_REPEAT, "Malformed repeat loop", debugInfo);
	}



	Error error::missingCondition(const DebugInfo & debugInfo) {
		return Error(ErrorCode::MISSING_CONDITION, "Expected condition", debugInfo);
	}

	Error error::missingIfBranch(const DebugInfo & debugInfo) {
		return Error(ErrorCode::MISSING_IF_BRANCH, "Expected statement after if", debugInfo);
	}

	Error error::missingReturnType(const DebugInfo & debugInfo) {
		return Error(ErrorCode::MISSING_RETURN_TYPE, "Missing return type" , debugInfo);
	}



	Error error::unopenedAsm(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNOPENED_ASM_BLOCK, "Expected { before assembly block", debugInfo);
	}

	Error error::unclosedAsm(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNCLOSED_ASM_BLOCK, "Expected } after assembly block", debugInfo);
	}

	Error error::unopenedParameterList(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNOPENED_PARAMETER_LIST, "Missing parameter list. Expected (", debugInfo);
	}

	Error error::unclosedParameterList(const DebugInfo & debugInfo) {
		return Error(ErrorCode::UNCLOSED_PARAMETER_LIST, "Unclosed parameter list. Expected )", debugInfo);
	}
}


