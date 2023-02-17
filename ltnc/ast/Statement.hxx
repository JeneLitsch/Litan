#pragma once
#include <vector>
#include "Node.hxx"
#include "Switch.hxx"
#include "ltnc/type/Type.hxx"
#include "ltn/casts.hxx"
#include "ltn/Visitor.hxx"
#include "Binding.hxx"

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
	struct StmtSwitch;
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
		StmtSwitch,
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
		virtual ~DoNothing() = default;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct Throw final : public Statement {
		Throw(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location) 
			: Statement(location)
			, expression(std::move(expression)) {}
		virtual ~Throw() = default;
		std::unique_ptr<Expression> expression;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct Block final : public Statement {
		Block(
			std::vector<std::unique_ptr<Statement>> statements,
			const SourceLocation & location) 
			: Statement(location)
			, statements(std::move(statements)) {}
		virtual ~Block() = default;
		std::vector<std::unique_ptr<Statement>> statements;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct NewVar final : public Statement {
		NewVar(
			std::unique_ptr<Binding> binding,
			std::unique_ptr<Expression> expression,
			const SourceLocation & location,
			const std::optional<type::IncompleteType> & type = type::IncompleteType{type::Any{}})
			: Statement(location)
			, binding(std::move(binding))
			, expression(std::move(expression))
			, type{type} {}
		virtual ~NewVar() = default;
		std::unique_ptr<Binding> binding;		
		std::unique_ptr<Expression> expression;
		std::optional<type::IncompleteType> type;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
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
		virtual ~IfElse() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> if_branch;
		std::unique_ptr<Statement> else_branch;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct While final : public Statement {
		While(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Statement(location)
			, condition(std::move(condition))
			, body(std::move(body)) {}

		virtual ~While() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct InfiniteLoop final : public Statement {
		InfiniteLoop(
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Statement(location)
			, body(std::move(body)) {}

		virtual ~InfiniteLoop() = default;
		std::unique_ptr<Statement> body;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
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

		virtual ~For() = default;
		std::string index_name;
		std::unique_ptr<Expression> from;
		std::unique_ptr<Expression> to;
		std::unique_ptr<Expression> step;
		std::unique_ptr<Statement> body;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
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

		virtual ~ForEach() = default;
		std::string index_name;
		std::unique_ptr<Expression> expr;
		std::unique_ptr<Statement> body;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct StatementExpression final : public Statement {
		StatementExpression(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			: Statement(location)
			, expression(std::move(expression)) {}
		virtual ~StatementExpression() = default;
		std::unique_ptr<Expression> expression;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct Return final : public Statement {
		Return(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			: Statement(location)
			, expression(std::move(expression)) {}
		virtual ~Return() = default;
		std::unique_ptr<Expression> expression;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
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
		virtual ~Assign() = default;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct StmtSwitch final : Switch<Statement>  {
		StmtSwitch(const SourceLocation & location)
			: Switch<Statement>{location} {}

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
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
			virtual void visit(const StmtSwitch & x)           const override { this->run(x); };
			virtual void visit(const StatementExpression & x)  const override { this->run(x); };
			virtual void visit(const DoNothing & x)            const override { this->run(x); };
			virtual void visit(const Assign & x)               const override { this->run(x); };
		};

		return Visitor{fx}(stmt);
	}
}