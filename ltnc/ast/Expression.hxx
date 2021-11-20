#pragma once
#include "Node.hxx"
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

	struct Index : public Expression {
		Index(
			std::unique_ptr<Expression> expression,
			std::unique_ptr<Expression> index,
			const lex::DebugInfo & debugInfo)
			:	Expression(debugInfo),
				expression(std::move(expression)),
				index(std::move(index)) {}
		virtual ~Index() = default;
		const std::unique_ptr<Expression> expression;
		const std::unique_ptr<Expression> index;
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
		enum class Type { ARRAY };
		New(const lex::DebugInfo & debugInfo, Type type)
			:	Primary(debugInfo), type(type) {}
		virtual ~New() = default;
		Type type;
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

	struct Call : public Expression {
	public:
		Call(
			const std::string & name,
			std::vector<std::unique_ptr<Expression>> parameters,
			const lex::DebugInfo & debugInfo)
			:	Expression(debugInfo),
				name(name),
				parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		const std::string name;
		const std::vector<std::unique_ptr<Expression>> parameters;
	};
}