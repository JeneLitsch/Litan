#pragma once
#include "ltn/Visitor.hxx"
#include <cstdint>
#include "Node.hxx"

namespace ltn::c::sst {
	struct Block;
	struct IfElse;
	struct While;
	struct InfiniteLoop;
	struct For;
	struct ForEach;
	struct Assign;
	struct Return;
	struct Throw;
	struct StmtSwitch;
	struct DoNothing;
	
	
	
	using StmtVisitor = Visitor<
		Block,
		IfElse,
		While,
		InfiniteLoop,
		For,
		ForEach,
		Assign,
		Return,
		Throw,
		StmtSwitch,
		DoNothing
	>;



	class Statement : public Node {
	public:
		Statement() {}

		virtual ~Statement() = default;

		virtual std::size_t nested_alloc() const = 0;
		virtual std::size_t direct_alloc() const = 0;

		virtual void accept(const StmtVisitor &) const = 0;
	};
}