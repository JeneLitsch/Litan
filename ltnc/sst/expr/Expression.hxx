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
	struct Conditional;
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
		Conditional,
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



	template<typename Ret>
	auto visit(const Expression & expr, auto && fx) {

		using Callable = std::decay_t<decltype(fx)>;
		using Base = FunctionVisitor<ExprVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 

			virtual void visit(const Binary & x) const override { this->run(x); };
			virtual void visit(const Unary & x) const override { this->run(x); };
			virtual void visit(const Integer & x) const override { this->run(x); };
			virtual void visit(const Float & x) const override { this->run(x); };
			virtual void visit(const Bool & x) const override { this->run(x); };
			virtual void visit(const Char & x) const override { this->run(x); };
			virtual void visit(const Null & x) const override { this->run(x); };
			virtual void visit(const String & x) const override { this->run(x); };
			virtual void visit(const Array & x) const override { this->run(x); };
			virtual void visit(const Tuple & x) const override { this->run(x); };
			virtual void visit(const Call & x) const override { this->run(x); };
			virtual void visit(const Conditional & x) const override { this->run(x); };
			virtual void visit(const Invoke & x) const override { this->run(x); };
			virtual void visit(const InvokeMember & x) const override { this->run(x); };
			virtual void visit(const Var & x) const override { this->run(x); };
			virtual void visit(const Index & x) const override { this->run(x); };
			virtual void visit(const FxPointer & x) const override { this->run(x); };
			virtual void visit(const Member & x) const override { this->run(x); };
			virtual void visit(const GlobalVar & x) const override { this->run(x); };
			virtual void visit(const Iife & x) const override { this->run(x); };
			virtual void visit(const Ternary & x) const override { this->run(x); };
			virtual void visit(const Switch & x) const override { this->run(x); };
			virtual void visit(const Reflect & x) const override { this->run(x); };
			virtual void visit(const Struct & x) const override { this->run(x); };
			virtual void visit(const Map & x) const override { this->run(x); };
			virtual void visit(const Type & x) const override { this->run(x); };
			virtual void visit(const BuildIn & x) const override { this->run(x); };
		};

		return Visitor{fx}(expr);
	}
}