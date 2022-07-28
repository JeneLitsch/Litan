#pragma once
#include "Expression.hxx"

namespace ltn::c::ast {
	struct Assignable : public Primary {
		virtual ~Assignable() = default;
		Assignable(const SourceLocation & location) : Primary(location) {}
	};



	struct Index final : public Assignable {
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



	struct Var final : public Assignable {
	public:
		Var(const std::string & name,
			const SourceLocation & location)
			:	Assignable(location),
				name(name) {}
		virtual ~Var() = default;
		std::string name;
	};



	struct GlobalVar final : public Assignable {
	public:
		GlobalVar(const std::string & name,
			const SourceLocation & location)
			:	Assignable(location),
				name(name) {}
		virtual ~GlobalVar() = default;
		std::string name;
	};



	struct Member final : public Assignable {
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