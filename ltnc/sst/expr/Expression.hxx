#pragma once
#include <cstdint>
#include <memory>
#include "ltn/Visitor.hxx"
#include "ltnc/sst/Node.hxx"
#include "ltnc/sst/types.hxx"

namespace ltn::c::sst::expr {

	struct Binary;
	struct Unary;
	struct Integer;
	struct Float;
	struct Bool;
	struct Char;
	struct Null;
	struct String;
	struct Array;
	struct Tuple;
	struct Call;
	struct Invoke;
	struct InvokeMember;
	struct Var;
	struct Index;
	struct FxPointer;
	struct Member;
	struct GlobalVar;
	struct Iife;
	struct Ternary;
	struct Switch;
	struct Reflect;
	struct Struct;
	struct Map;
	struct Type;
	struct BuildIn;



	using ExprVisitor = Visitor<
		Binary,
		Unary,
		Integer,
		Float,
		Bool,
		Char,
		Null,
		String,
		Array,
		Tuple,
		Call,
		Invoke,
		InvokeMember,
		Var,
		Index,
		FxPointer,
		Member,
		GlobalVar,
		Iife,
		Ternary,
		Switch,
		Reflect,
		Struct,
		Map,
		Type,
		BuildIn
	>;



	struct Expression : public Node {
		Expression() {}
			
		virtual ~Expression() = default;

		virtual std::uint64_t alloc() const = 0;
		virtual void accept(const ExprVisitor &) const = 0;
	
		virtual bind_ptr convert_to_bindung() && { return nullptr; }
	};


	
	template<typename Derived>
	struct ExpressionCRTP : Expression {
		virtual void accept(const ExprVisitor & visitor) const override {
			return visitor.visit(static_cast<const Derived &>(*this));
		}
	};
}