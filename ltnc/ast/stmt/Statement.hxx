#pragma once
#include <vector>
#include "ltn/casts.hxx"
#include "ltn/Visitor.hxx"
#include "ltnc/ast/Node.hxx"
#include "ltnc/ast/expr/Expression.hxx"
#include "ltnc/ast/types.hxx"

namespace ltn::c::ast::stmt {
	struct Block;
	struct IfElse;
	struct While;
	struct InfiniteLoop;
	struct ForEach;
	struct NewVar;
	struct Return;
	struct Throw;
	struct Switch;
	struct StatementExpression;
	struct NoOp;
	struct Assign;



	using StmtVisitor = Visitor<
		Block,
		IfElse,
		While,
		InfiniteLoop,
		ForEach,
		NewVar,
		Return,
		Throw,
		Switch,
		StatementExpression,
		NoOp,
		Assign
	>;



	struct Statement : public Node {
		Statement(const SourceLocation & location) : Node(location) {}

		virtual ~Statement() = default;
		virtual void accept(const StmtVisitor &) const = 0;
	};


	
	struct NoOp final : public Statement {
		NoOp(const SourceLocation & location) : Statement(location) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}
	};



	struct Throw final : public Statement {
		Throw(
			expr_ptr expr,
			const SourceLocation & location) 
			: Statement(location)
			, expr(std::move(expr)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		expr_ptr expr;
	};



	struct Block final : public Statement {
		Block(
			std::vector<stmt_ptr> statements,
			const SourceLocation & location) 
			: Statement(location)
			, statements(std::move(statements)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<stmt_ptr> statements;
	};



	struct NewVar final : public Statement {
		NewVar(
			bind_ptr binding,
			expr_ptr expr,
			const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~NewVar(); 

		bind_ptr binding;		
		expr_ptr expr;
	};



	struct IfElse final : public Statement {
		IfElse(
			expr_ptr condition,
			stmt_ptr if_branch,
			stmt_ptr else_branch,
			const SourceLocation & location)
			: Statement(location)
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		expr_ptr condition;
		stmt_ptr if_branch;
		stmt_ptr else_branch;
	};



	struct While final : public Statement {
		While(
			expr_ptr condition,
			stmt_ptr body,
			const SourceLocation & location)
			: Statement(location)
			, condition(std::move(condition))
			, body(std::move(body)) {}


		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		expr_ptr condition;
		stmt_ptr body;
	};



	struct InfiniteLoop final : public Statement {
		InfiniteLoop(
			stmt_ptr body,
			const SourceLocation & location)
			: Statement(location)
			, body(std::move(body)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		stmt_ptr body;
	};



	struct ForEach final : public Statement {
		ForEach(
			std::string index_name,
			expr_ptr expr,
			stmt_ptr body,
			const SourceLocation & location)
			: Statement(location)
			, index_name(std::move(index_name))
			, expr(std::move(expr))
			, body(std::move(body)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::string index_name;
		expr_ptr expr;
		stmt_ptr body;
	};



	struct StatementExpression final : public Statement {
		StatementExpression(
			expr_ptr expr,
			const SourceLocation & location)
			: Statement(location)
			, expr(std::move(expr)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		expr_ptr expr;
	};



	struct Return final : public Statement {
		Return(
			expr_ptr expr,
			const SourceLocation & location)
			: Statement(location)
			, expr(std::move(expr)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		expr_ptr expr;
	};



	struct Assign final : public Statement {
	public:
		Assign(
			expr_ptr l,
			expr_ptr r,
			const SourceLocation & location)
			: Statement(location)
			, l(std::move(l))
			, r(std::move(r)) {}

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		expr_ptr l;
		expr_ptr r;
	};



	struct Switch : Statement {
		Switch(const SourceLocation & location)
			: Statement(location) {}

		expr_ptr condition;

		std::vector<std::pair<
			expr_ptr,
			stmt_ptr
		>> cases;

		stmt_ptr d3fault;

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
			virtual void visit(const ForEach & x)              const override { this->run(x); };
			virtual void visit(const NewVar & x)               const override { this->run(x); };
			virtual void visit(const Return & x)               const override { this->run(x); };
			virtual void visit(const Throw & x)                const override { this->run(x); };
			virtual void visit(const Switch & x)           const override { this->run(x); };
			virtual void visit(const StatementExpression & x)  const override { this->run(x); };
			virtual void visit(const NoOp & x)            const override { this->run(x); };
			virtual void visit(const Assign & x)               const override { this->run(x); };
		};

		return Visitor{fx}(stmt);
	}
}