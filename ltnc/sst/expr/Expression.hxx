#pragma once
#include <cstdint>
#include <memory>
#include "ltn/Visitor.hxx"
#include "ltnc/sst/Node.hxx"

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
	struct FxPointer;
	struct Member;
	struct GlobalVar;
	struct Iife;
	struct Ternary;
	struct Choose;
	struct Reflect;
	struct InitStruct;
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
		Choose,
		Reflect,
		InitStruct,
		Map,
		Type,
		BuildIn
	>;



	struct Expression : public Node {
		Expression() {}
			
		virtual ~Expression() = default;

		virtual std::uint64_t alloc() const = 0;
		virtual void accept(const ExprVisitor &) const = 0;

	};


	
	template<typename Derived>
	struct ExpressionCRTP : Expression {
		virtual void accept(const ExprVisitor & visitor) const override {
			return visitor.visit(static_cast<const Derived &>(*this));
		}
	};


	using expr_ptr = std::unique_ptr<Expression>;
}