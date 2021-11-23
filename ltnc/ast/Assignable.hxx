#pragma once
#include "Expression.hxx"

namespace ltn::c::ast {
	struct Assignable : public Primary {
		virtual ~Assignable() = default;
		Assignable(const lex::DebugInfo & debugInfo) : Primary(debugInfo) {}
	};

	struct Index : public Assignable {
		Index(
			std::unique_ptr<Expression> expression,
			std::unique_ptr<Expression> index,
			const lex::DebugInfo & debugInfo)
			:	Assignable(debugInfo),
				expression(std::move(expression)),
				index(std::move(index)) {}
		virtual ~Index() = default;
		const std::unique_ptr<Expression> expression;
		const std::unique_ptr<Expression> index;
	};

	struct Var : public Assignable {
	public:
		Var(const std::string & name,
			const lex::DebugInfo & debugInfo)
			:	Assignable(debugInfo),
				name(name) {}
		virtual ~Var() = default;
		const std::string name;
	};

	struct Assign : public Expression {
	public:
		Assign(
			std::unique_ptr<Assignable> l,
			std::unique_ptr<Expression> r,
			const lex::DebugInfo & debugInfo)
			:	Expression(debugInfo), l(std::move(l)), r(std::move(r)) {}
		virtual ~Assign() = default;
		const std::unique_ptr<Assignable> l;
		const std::unique_ptr<Expression> r;
	};
}