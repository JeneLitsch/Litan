#pragma once
#include "Node.hxx"
#include "ltnc/type/Type.hxx"
#include <vector>
namespace ltn::c::ast {
	struct Expression : public Node {
		virtual ~Expression() = default;
	};



	struct Literal : public Expression {
		virtual ~Literal() = default;
	};

	struct Integer : public Literal {
	public:
		Integer(std::int64_t value)
			:	value(value) {}
		virtual ~Integer() = default;
		std::int64_t value;
	};

	struct Float : public Literal {
	public:
		Float(double value)
			:	value(value) {}
		virtual ~Float() = default;
		double value;
	};

	struct Bool : public Literal {
	public:
		Bool(bool value)
			:	value(value) {}
		virtual ~Bool() = default;
		bool value;
	};



	struct Unary : public Expression {
		enum class Type { NEG, NOT };
		Unary(Type type, std::unique_ptr<Expression> expression)
			:	type(type), expression(std::move(expression)) {}
		virtual ~Unary() = default;
		Type type;
		std::unique_ptr<Expression> expression;
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
			std::unique_ptr<Expression> r)
			:	type(type), l(std::move(l)), r(std::move(r)) {}
		virtual ~Binary() = default;
		Type type;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};


	struct Var : public Expression {
	public:
		Var(const std::string & name)
			:	name(name) {}
		virtual ~Var() = default;
		std::string name;
	};


	struct New : public Literal {
	public:
		New(type::Type type)
			:	type(std::move(type)) {}
		virtual ~New() = default;
		type::Type type;
	};


	struct Assign : public Literal {
	public:
		Assign(
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r)
			:	l(std::move(l)), r(std::move(r)) {}
		virtual ~Assign() = default;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};
}