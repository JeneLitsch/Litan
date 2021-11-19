#pragma once
#include "Node.hxx"
#include "ltnc/type/Type.hxx"
#include <vector>
namespace ltn::c::ast {
	struct Expression : public Node {
		Expression(const lex::DebugInfo & debugInfo) : Node(debugInfo) {}
		virtual ~Expression() = default;
	};

	struct Primary : public Expression {
		Primary(const lex::DebugInfo & debugInfo) : Expression(debugInfo) {}
		virtual ~Primary() = default;
	};

	struct Literal : public Primary {
		Literal(const lex::DebugInfo & debugInfo) : Primary(debugInfo) {}
		virtual ~Literal() = default;
	};

	struct Integer : public Literal {
	public:
		Integer(std::int64_t value, const lex::DebugInfo & debugInfo)
			:	Literal(debugInfo), value(value) {}
		virtual ~Integer() = default;
		const std::int64_t value;
	};

	struct Float : public Literal {
	public:
		Float(double value, const lex::DebugInfo & debugInfo)
			:	Literal(debugInfo), value(value) {}
		virtual ~Float() = default;
		const double value;
	};

	struct Bool : public Literal {
	public:
		Bool(bool value, const lex::DebugInfo & debugInfo)
			:	Literal(debugInfo), value(value) {}
		virtual ~Bool() = default;
		const bool value;
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


	struct Var : public Primary {
	public:
		Var(const std::string & name,
			const lex::DebugInfo & debugInfo)
			:	Primary(debugInfo),
				name(name) {}
		virtual ~Var() = default;
		const std::string name;
	};


	struct New : public Primary {
	public:
		New(type::Type type,
			const lex::DebugInfo & debugInfo)
			:	Primary(debugInfo), type(std::move(type)) {}
		virtual ~New() = default;
		const type::Type type;
	};


	struct Assign : public Expression {
	public:
		Assign(
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const lex::DebugInfo & debugInfo)
			:	Expression(debugInfo), l(std::move(l)), r(std::move(r)) {}
		virtual ~Assign() = default;
		const std::unique_ptr<Expression> l;
		const std::unique_ptr<Expression> r;
	};
}