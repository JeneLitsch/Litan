#pragma once
#include <cstdint>
#include <memory>
#include "ltnc/type/Type.hxx"
#include "ltn/Visitor.hxx"
#include "Node.hxx"

namespace ltn::c::sst {
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
	struct Var;
	struct Index;
	struct Lambda;
	struct FxPointer;
	struct Member;
	struct GlobalVar;
	struct Iife;
	struct Ternary;
	struct ExprSwitch;
	struct TypedUnary;
	struct Reflect;
	struct InitStruct;



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
		Var,
		Index,
		Lambda,
		FxPointer,
		Member,
		GlobalVar,
		Iife,
		Ternary,
		ExprSwitch,
		TypedUnary,
		Reflect,
		InitStruct
	>;



	struct Expression : public Node {
		virtual ~Expression() = default;
		type::Type type;

		virtual std::uint64_t alloc() const = 0;
		virtual void accept(const ExprVisitor &) const = 0;
	protected:
		Expression(const type::Type & type)
			: type{type} {}
	};
	using expr_ptr = std::unique_ptr<Expression>;
}