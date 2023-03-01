#pragma once
#include <vector>
#include "ltn/casts.hxx"
#include "ltn/Visitor.hxx"
#include "ltnc/type/Type.hxx"
#include "ltnc/ast/Node.hxx"
#include "ltnc/ast/bind/Binding.hxx"

namespace ltn::c::ast {
	struct Expression;



	struct Block;
	struct IfElse;
	struct While;
	struct InfiniteLoop;
	struct For;
	struct ForEach;
	struct NewVar;
	struct Return;
	struct Throw;
	struct Switch;
	struct StatementExpression;
	struct DoNothing;
	struct Assign;



	using StmtVisitor = Visitor<
		Block,
		IfElse,
		While,
		InfiniteLoop,
		For,
		ForEach,
		NewVar,
		Return,
		Throw,
		Switch,
		StatementExpression,
		DoNothing,
		Assign
	>;



	class Statement : public Node {
	public:
		Statement(const SourceLocation & location) : Node(location) {}

		virtual ~Statement() = default;
		virtual void accept(const StmtVisitor &) const = 0;
	};


	
	struct DoNothing final : public Statement {
		DoNothing(const SourceLocation & location) : Statement(location) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}
	};



	struct Throw final : public Statement {
		Throw(
			std::unique_ptr<Expression> expr,
			const SourceLocation & location) 
			: Statement(location)
			, expr(std::move(expr)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> expr;
	};



	struct Block final : public Statement {
		Block(
			std::vector<std::unique_ptr<Statement>> statements,
			const SourceLocation & location) 
			: Statement(location)
			, statements(std::move(statements)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<std::unique_ptr<Statement>> statements;
	};



	struct NewVar final : public Statement {
		NewVar(
			std::unique_ptr<Binding> binding,
			std::unique_ptr<Expression> expr,
			const SourceLocation & location,
			const std::optional<type::IncompleteType> & type = type::IncompleteType{type::Any{}})
			: Statement(location)
			, binding(std::move(binding))
			, expr(std::move(expr))
			, type{type} {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Binding> binding;		
		std::unique_ptr<Expression> expr;
		std::optional<type::IncompleteType> type;
	};



	struct IfElse final : public Statement {
		IfElse(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> if_branch,
			std::unique_ptr<Statement> else_branch,
			const SourceLocation & location)
			: Statement(location)
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> if_branch;
		std::unique_ptr<Statement> else_branch;
	};



	struct While final : public Statement {
		While(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Statement(location)
			, condition(std::move(condition))
			, body(std::move(body)) {}


		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
	};



	struct InfiniteLoop final : public Statement {
		InfiniteLoop(
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Statement(location)
			, body(std::move(body)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Statement> body;
	};



	struct For final : public Statement {
		For(
			std::string index_name,
			std::unique_ptr<Expression> from,
			std::unique_ptr<Expression> to,
			std::unique_ptr<Expression> step,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Statement(location)
			, index_name(std::move(index_name))
			, from(std::move(from))
			, to(std::move(to))
			, step(std::move(step))
			, body(std::move(body)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::string index_name;
		std::unique_ptr<Expression> from;
		std::unique_ptr<Expression> to;
		std::unique_ptr<Expression> step;
		std::unique_ptr<Statement> body;
	};



	struct ForEach final : public Statement {
		ForEach(
			std::string index_name,
			std::unique_ptr<Expression> expr,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Statement(location)
			, index_name(std::move(index_name))
			, expr(std::move(expr))
			, body(std::move(body)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::string index_name;
		std::unique_ptr<Expression> expr;
		std::unique_ptr<Statement> body;
	};



	struct StatementExpression final : public Statement {
		StatementExpression(
			std::unique_ptr<Expression> expr,
			const SourceLocation & location)
			: Statement(location)
			, expr(std::move(expr)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> expr;
	};



	struct Return final : public Statement {
		Return(
			std::unique_ptr<Expression> expr,
			const SourceLocation & location)
			: Statement(location)
			, expr(std::move(expr)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> expr;
	};



	struct Assign final : public Statement {
	public:
		Assign(
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			: Statement(location)
			, l(std::move(l))
			, r(std::move(r)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};



	struct Switch : Statement {
		Switch(const SourceLocation & location)
			: Statement(location) {}

		std::unique_ptr<Expression> condition;

		std::vector<std::pair<
			std::unique_ptr<Expression>,
			std::unique_ptr<Statement>
		>> cases;

		std::unique_ptr<Statement> d3fault;

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}
	};



	auto visit_statement(const Statement & stmt, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, Block>;
		using Base = FunctionVisitor<StmtVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base{fx} {}

			virtual void visit(const Block & x)                const override { this->run(x); };
			virtual void visit(const IfElse & x)               const override { this->run(x); };
			virtual void visit(const While & x)                const override { this->run(x); };
			virtual void visit(const InfiniteLoop & x)         const override { this->run(x); };
			virtual void visit(const For & x)                  const override { this->run(x); };
			virtual void visit(const ForEach & x)              const override { this->run(x); };
			virtual void visit(const NewVar & x)               const override { this->run(x); };
			virtual void visit(const Return & x)               const override { this->run(x); };
			virtual void visit(const Throw & x)                const override { this->run(x); };
			virtual void visit(const Switch & x)           const override { this->run(x); };
			virtual void visit(const StatementExpression & x)  const override { this->run(x); };
			virtual void visit(const DoNothing & x)            const override { this->run(x); };
			virtual void visit(const Assign & x)               const override { this->run(x); };
		};

		return Visitor{fx}(stmt);
	}
}