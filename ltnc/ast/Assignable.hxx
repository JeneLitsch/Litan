#pragma once
#include "Expression.hxx"

namespace ltn::c::ast {
	struct Assignable : public Primary {
		virtual ~Assignable() = default;
		Assignable(const SourceLocation & location) : Primary(location) {}
	};



	struct Index : public Assignable {
		Index(
			std::unique_ptr<Expression> expression,
			std::unique_ptr<Expression> index,
			const SourceLocation & location)
			:	Assignable(location),
				expression(std::move(expression)),
				index(std::move(index)) {}
		virtual ~Index() = default;
		std::unique_ptr<Expression> expression;
		std::unique_ptr<Expression> index;
	};



	struct Var : public Assignable {
	public:
		Var(const std::string & name,
			const SourceLocation & location)
			:	Assignable(location),
				name(name) {}
		virtual ~Var() = default;
		std::string name;
	};



	struct Assign : public Expression {
	public:
		Assign(
			std::unique_ptr<Assignable> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			:	Expression(location), l(std::move(l)), r(std::move(r)) {}
		virtual ~Assign() = default;
		std::unique_ptr<Assignable> l;
		std::unique_ptr<Expression> r;
	};



	struct Modify : public Expression {
		enum class Type { ADD, SUB, MLT, DIV, MOD, SHIFT_L, SHIFT_R };
		Modify(
			Type type,
			std::unique_ptr<Assignable> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			:	Expression(location),
				type(type),
				l(std::move(l)),
				r(std::move(r)) {}
		virtual ~Modify() = default;
		Type type;
		std::unique_ptr<Assignable> l;
		std::unique_ptr<Expression> r;
	};



	struct Member : public Assignable {
		Member(
			std::unique_ptr<Expression> expr,
			const std::string & name,
			const SourceLocation & location)
			:	Assignable(location),
				expr(std::move(expr)),
				name(std::move(name)){};
		virtual ~Member() = default;
		std::unique_ptr<Expression> expr;
		std::string name;
	};
}