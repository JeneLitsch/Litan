#pragma once
#include <cstdint>
#include "ltn/Visitor.hxx"
#include "ltnc/sst/Node.hxx"

namespace ltn::c::sst {
	struct Block;
	struct IfElse;
	struct While;
	struct InfiniteLoop;
	struct ForEach;
	struct Assign;
	struct Return;
	struct Throw;
	struct Switch;
	struct NoOp;
	
	
	
	using StmtVisitor = Visitor<
		Block,
		IfElse,
		While,
		InfiniteLoop,
		ForEach,
		Assign,
		Return,
		Throw,
		Switch,
		NoOp
	>;



	class Statement : public Node {
	public:
		Statement() {}

		virtual ~Statement() = default;

		virtual std::size_t nested_alloc() const = 0;
		virtual std::size_t direct_alloc() const = 0;

		virtual void accept(const StmtVisitor &) const = 0;
	};



	using stmt_ptr = std::unique_ptr<Statement>;
}