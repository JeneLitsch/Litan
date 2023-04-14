#pragma once
#include <cstdint>
#include <memory>
#include "ltn/Visitor.hxx"
#include "ltnc/sst/Node.hxx"
#include "ltnc/type/Type.hxx"

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
	struct InvokeMember;
	struct Var;
	struct Index;
	struct Lambda;
	struct FxPointer;
	struct Member;
	struct GlobalVar;
	struct Iife;
	struct Ternary;
	struct Choose;
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
		InvokeMember,
		Var,
		Index,
		Lambda,
		FxPointer,
		Member,
		GlobalVar,
		Iife,
		Ternary,
		Choose,
		TypedUnary,
		Reflect,
		InitStruct
	>;



	struct Expression : public Node {
		Expression(const type::Type & type)
			: type{type} {}
			
		virtual ~Expression() = default;

		virtual std::uint64_t alloc() const = 0;
		virtual void accept(const ExprVisitor &) const = 0;
		
		type::Type type;

	};
	using expr_ptr = std::unique_ptr<Expression>;
}