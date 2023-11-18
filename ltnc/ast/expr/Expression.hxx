#pragma once
#include <vector>
#include <utility>
#include <any>
#include <variant>
#include <bitset>
#include "ltn/casts.hxx"
#include "ltn/Visitor.hxx"
#include "ltn/MemberCode.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/Operations.hxx"
#include "ltnc/ast/Node.hxx"
#include "ltnc/ast/types.hxx"


namespace ltn::c::ast::expr {
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
	struct InvokeMember;
	struct Var;
	struct Index;
	struct Lambda;
	struct FxPointer;
	struct Member;
	struct Iife;
	struct Ternary;
	struct Choose;
	struct Reflect;
	struct ForwardDynamicCall;
	struct Struct;
	struct Map;
	struct Type;
	struct CustomLiteral;
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
		InvokeMember,
		Var,
		Index,
		Lambda,
		FxPointer,
		Member,
		Iife,
		Ternary,
		Choose,
		Reflect,
		ForwardDynamicCall,
		Struct,
		Map,
		Type,
		CustomLiteral,
		BuildIn
	>;



	struct Expression : public Node {
		Expression(const SourceLocation & location) : Node(location) {}
		
		virtual ~Expression() = default;
		virtual void accept(const ExprVisitor & visitor) const = 0;
	};



	auto visit(const Expression & expr, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, Binary>;
		using Base = FunctionVisitor<ExprVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 

			virtual void visit(const Binary & x)             const override { this->run(x); };
			virtual void visit(const Unary & x)              const override { this->run(x); };
			virtual void visit(const Integer & x)            const override { this->run(x); };
			virtual void visit(const Float & x)              const override { this->run(x); };
			virtual void visit(const Bool & x)               const override { this->run(x); };
			virtual void visit(const Char & x)               const override { this->run(x); };
			virtual void visit(const Null & x)               const override { this->run(x); };
			virtual void visit(const String & x)             const override { this->run(x); };
			virtual void visit(const Array & x)              const override { this->run(x); };
			virtual void visit(const Tuple & x)              const override { this->run(x); };
			virtual void visit(const Call & x)               const override { this->run(x); };
			virtual void visit(const InvokeMember & x)       const override { this->run(x); };
			virtual void visit(const Var & x)                const override { this->run(x); };
			virtual void visit(const Index & x)              const override { this->run(x); };
			virtual void visit(const Lambda & x)             const override { this->run(x); };
			virtual void visit(const FxPointer & x)          const override { this->run(x); };
			virtual void visit(const Member & x)             const override { this->run(x); };
			virtual void visit(const Iife & x)               const override { this->run(x); };
			virtual void visit(const Ternary & x)            const override { this->run(x); };
			virtual void visit(const Choose & x)             const override { this->run(x); };
			virtual void visit(const Reflect & x)            const override { this->run(x); };
			virtual void visit(const ForwardDynamicCall & x) const override { this->run(x); };
			virtual void visit(const Struct & x)         const override { this->run(x); };
			virtual void visit(const Map & x)                const override { this->run(x); };
			virtual void visit(const Type & x)               const override { this->run(x); };
			virtual void visit(const CustomLiteral & x)      const override { this->run(x); };
			virtual void visit(const BuildIn & x)         const override { this->run(x); };
		};

		return Visitor{fx}(expr);
	}
}