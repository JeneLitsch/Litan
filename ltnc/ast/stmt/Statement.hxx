#pragma once
#include <vector>
#include "ltn/casts.hxx"
#include "ltn/Visitor.hxx"
#include "ltnc/ast/Node.hxx"
#include "ltnc/ast/types.hxx"

namespace ltn::c::ast::stmt {
	struct Block;
	struct IfElse;
	struct While;
	struct InfiniteLoop;
	struct ForEach;
	struct NewVar;
	struct Return;
	struct Yield;
	struct Throw;
	struct Switch;
	struct StatementExpression;
	struct Conditional;
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
		Conditional,
		NoOp,
		Assign,
		Yield
	>;



	struct Statement : public Node {
		Statement(const SourceLocation & location) : Node(location) {}

		virtual ~Statement() = default;
		virtual void accept(const StmtVisitor &) const = 0;
	};



	template<typename Ret>
	auto visit(const Statement & stmt, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Base = FunctionVisitor<StmtVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base{fx} {}

			virtual void visit(const Block & x)               const override { this->run(x); };
			virtual void visit(const IfElse & x)              const override { this->run(x); };
			virtual void visit(const While & x)               const override { this->run(x); };
			virtual void visit(const InfiniteLoop & x)        const override { this->run(x); };
			virtual void visit(const ForEach & x)             const override { this->run(x); };
			virtual void visit(const NewVar & x)              const override { this->run(x); };
			virtual void visit(const Return & x)              const override { this->run(x); };
			virtual void visit(const Throw & x)               const override { this->run(x); };
			virtual void visit(const Switch & x)              const override { this->run(x); };
			virtual void visit(const StatementExpression & x) const override { this->run(x); };
			virtual void visit(const Conditional & x)         const override { this->run(x); };
			virtual void visit(const NoOp & x)                const override { this->run(x); };
			virtual void visit(const Assign & x)              const override { this->run(x); };
			virtual void visit(const Yield & x)               const override { this->run(x); };
		};

		return Visitor{fx}(stmt);
	}
}