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
	struct Assignable;



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


	
	struct DoNothing : public Statement {
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

	struct StmtSwitch : Switch<Statement>  {
		StmtSwitch(const SourceLocation & location)
			: Switch<Statement>{location} {}

		virtual void accept(const StmtVisitor & visitor) const override { visitor.visit(*this); }
	};



	template<typename Callable>
	class StmtVisitorImpl : public StmtVisitor {
		using Ret = decltype(std::declval<const Callable &>()(std::declval<const ast::Block &>())); 
	public:
		StmtVisitorImpl(Callable fx) : fx{fx} {}

		virtual void visit(const ast::Block & x)                const override { ret = fx(x); };
		virtual void visit(const ast::IfElse & x)               const override { ret = fx(x); };
		virtual void visit(const ast::While & x)                const override { ret = fx(x); };
		virtual void visit(const ast::InfiniteLoop & x)         const override { ret = fx(x); };
		virtual void visit(const ast::For & x)                  const override { ret = fx(x); };
		virtual void visit(const ast::ForEach & x)              const override { ret = fx(x); };
		virtual void visit(const ast::NewVar & x)               const override { ret = fx(x); };
		virtual void visit(const ast::Return & x)               const override { ret = fx(x); };
		virtual void visit(const ast::Throw & x)                const override { ret = fx(x); };
		virtual void visit(const ast::StmtSwitch & x)           const override { ret = fx(x); };
		virtual void visit(const ast::StatementExpression & x)  const override { ret = fx(x); };
		virtual void visit(const ast::DoNothing & x)            const override { ret = fx(x); };
		virtual void visit(const ast::Assign & x)               const override { ret = fx(x); };

		Ret operator()(const ast::Statement & expr) const {
			expr.accept(*this);
			return std::move(ret);
		}
	private:
		Callable fx;
		mutable Ret ret;
	};



	auto visit_statement(const ast::Statement & stmt, auto && fx) {
		const auto visitor = StmtVisitorImpl{fx};
		return visitor(stmt);
	}
}