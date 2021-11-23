#pragma once
#include "Node.hxx"
#include <vector>

namespace ltn::c::ast {
	class Assignable;

	struct Expression : public Node {
		Expression(const lex::DebugInfo & debugInfo) : Node(debugInfo) {}
		virtual ~Expression() = default;
	};

	struct Primary : public Expression {
		Primary(const lex::DebugInfo & debugInfo) : Expression(debugInfo) {}
		virtual ~Primary() = default;
	};

	struct Unary : public Expression {
		enum class Type { NEG, NOT };
		Unary(
			Type type,
			std::unique_ptr<Expression> expression,
			const lex::DebugInfo & debugInfo)
			:	Expression(debugInfo),
				type(type),
				expression(std::move(expression)) {}
		virtual ~Unary() = default;
		const Type type;
		const std::unique_ptr<Expression> expression;
	};

	struct Binary : public Expression {
		enum class Type {
			ADD, SUB,
			MLT, DIV, MOD,
			BIGGER, SMALLER, BIGGEREQUAL, SMALLEREQUAL,
			EQUAL, UNEQUEL, };
		Binary(
			Type type,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const lex::DebugInfo & debugInfo)
			:	Expression(debugInfo),
				type(type),
				l(std::move(l)),
				r(std::move(r)) {}
		virtual ~Binary() = default;
		const Type type;
		const std::unique_ptr<Expression> l;
		const std::unique_ptr<Expression> r;
	};







	struct Call : public Primary {
	public:
		Call(
			const std::string & name,
			std::vector<std::unique_ptr<Expression>> parameters,
			const lex::DebugInfo & debugInfo)
			:	Primary(debugInfo),
				name(name),
				parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		const std::string name;
		const std::vector<std::unique_ptr<Expression>> parameters;
	};
}