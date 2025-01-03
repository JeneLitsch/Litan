#pragma once
#include <cstdint>
#include "litan_core/Visitor.hxx"
#include "litan_compiler/sst/Node.hxx"
#include "litan_compiler/sst/types.hxx"

namespace ltn::c::sst::stmt {
	struct Block;
	struct Conditional;
	struct IfElse;
	struct While;
	struct InfiniteLoop;
	struct ForEach;
	struct Assign;
	struct Return;
	struct Throw;
	struct Switch;
	struct NoOp;
	struct Yield;
	struct CoReturn;
	
	
	
	using StmtVisitor = Visitor<
		Block,
		Conditional,
		IfElse,
		While,
		InfiniteLoop,
		ForEach,
		Assign,
		Return,
		Throw,
		Switch,
		NoOp,
		Yield,
		CoReturn
	>;



	struct Statement : public Node {
	public:
		Statement() {}

		virtual ~Statement() = default;

		virtual std::size_t temporary_alloc() const = 0;
		virtual std::size_t persistent_alloc() const = 0;

		std::size_t total_alloc() const {
			return this->temporary_alloc() + this->persistent_alloc();
		}

		virtual void accept(const StmtVisitor &) const = 0;
	};



	template<typename Ret>
	auto visit(const Statement & stmt, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Base = FunctionVisitor<StmtVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 
			
			virtual void visit(const Block & x)        const override { this->run(x); }
			virtual void visit(const Conditional & x)  const override { this->run(x); }
			virtual void visit(const IfElse & x)       const override { this->run(x); }
			virtual void visit(const While & x)        const override { this->run(x); }
			virtual void visit(const InfiniteLoop & x) const override { this->run(x); }
			virtual void visit(const ForEach & x)      const override { this->run(x); }
			virtual void visit(const Assign & x)       const override { this->run(x); }
			virtual void visit(const Return & x)       const override { this->run(x); }
			virtual void visit(const Throw & x)        const override { this->run(x); }
			virtual void visit(const Switch & x)       const override { this->run(x); }
			virtual void visit(const NoOp & x)         const override { this->run(x); }
			virtual void visit(const Yield & x)        const override { this->run(x); }
			virtual void visit(const CoReturn & x)     const override { this->run(x); }
		};

		return Visitor{fx}(stmt);
	}
}