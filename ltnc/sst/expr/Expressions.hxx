#pragma once
#include <vector>
#include <bitset>
#include <variant>
#include "ltn/casts.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/Operations.hxx"
#include "ltnc/sst/expr/Expression.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/Statement.hxx"


namespace ltn::c::sst {
	struct Expression;
	struct Var;
	struct Function;
	class Statement;



	struct Var final : public Expression {
	public:
		Var(
			std::size_t address)
			: Expression{}
			, address{address} {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::size_t address;
	};



	struct GlobalVar final : public Expression {
	public:
		GlobalVar(
			std::size_t address)
			: Expression{}
			, address { address } {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::size_t address;
	};



	struct Member final : public Expression {
		Member(
			std::unique_ptr<Expression> expr,
			std::size_t address)
			: Expression{}
			, expr(std::move(expr))
			, address { address } {};

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> expr;
		std::size_t address;
	};



	struct Iife final : public Expression {
		Iife(
			std::string return_label,
			std::unique_ptr<Statement> stmt) 
			: Expression{}
			, return_label{return_label}
			, stmt(std::move(stmt)) {}

		virtual std::uint64_t alloc() const override {
			return this->stmt->direct_alloc() + this->stmt->nested_alloc();
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::string return_label;
		std::unique_ptr<Statement> stmt;
	};



	struct FxPointer final : public Expression {
		FxPointer(
			const Label & label,
			std::size_t arity,
			bool is_variadic)
			: Expression{}
			, label{label}
			, arity{arity}
			, is_variadic{is_variadic} {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		Label label;
		std::size_t arity;
		std::vector<std::unique_ptr<Var>> captures;
		bool is_variadic;
	};



	struct Choose final : Expression {
		Choose() : Expression{} {}

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & [c4se, expr] : this->cases) {
				count = std::max({c4se->alloc(), expr->alloc(), count});
			}
			return count;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> condition;

		std::vector<std::pair<
			std::unique_ptr<Expression>,
			std::unique_ptr<Expression>
		>> cases;

		std::unique_ptr<Expression> d3fault;
	};
	


	struct Type final : Expression {
		Type(std::vector<std::uint8_t> type_code)
			: Expression{}
			, type_code{std::move(type_code)} {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<std::uint8_t> type_code;
	};



	struct BuildIn final : Expression {
		BuildIn(std::string key)
			: Expression{}
			, key{std::move(key)} {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::string key;
	};
}