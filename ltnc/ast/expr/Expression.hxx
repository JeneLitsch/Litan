#pragma once
#include <vector>
#include <utility>
#include <any>
#include <variant>
#include <bitset>
#include "ltn/casts.hxx"
#include "ltn/Visitor.hxx"
#include "ltn/reserved_members.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/Operations.hxx"
#include "ltnc/ast/Node.hxx"
#include "ltnc/ast/types.hxx"


namespace ltn::c::ast::expr {
	struct Array;
	struct Binary;
	struct Bool;
	struct BuildIn;
	struct Call;
	struct Char;
	struct Choose;
	struct Conditional;
	struct CustomLiteral;
	struct Float;
	struct FxPointer;
	struct ForwardDynamicCall;
	struct Iife;
	struct Index;
	struct Integer;
	struct InvokeMember;
	struct Lambda;
	struct Map;
	struct Member;
	struct Null;
	struct Unary;
	struct Reflect;
	struct String;
	struct Struct;
	struct Ternary;
	struct Tuple;
	struct Type;
	struct Var;



	using ExprVisitor = Visitor<
		Array,
		Binary,
		Bool,
		BuildIn,
		Call,
		Char,
		Choose,
		Conditional,
		CustomLiteral,
		Float,
		FxPointer,
		ForwardDynamicCall,
		Iife,
		Index,
		Integer,
		InvokeMember,
		Lambda,
		Map,
		Member,
		Null,
		Unary,
		Reflect,
		String,
		Struct,
		Ternary,
		Tuple,
		Type,
		Var
	>;



	struct Expression : public Node {
		Expression(const SourceLocation & location) : Node(location) {}
		
		virtual ~Expression() = default;
		virtual void accept(const ExprVisitor & visitor) const = 0;
	};


	template<typename Ret>
	auto visit(const Expression & expr, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Base = FunctionVisitor<ExprVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 


			virtual void visit(const Array & x)              const override { this->run(x); }
			virtual void visit(const Binary & x)             const override { this->run(x); }
			virtual void visit(const Bool & x)               const override { this->run(x); }
			virtual void visit(const BuildIn & x)            const override { this->run(x); }
			virtual void visit(const Call & x)               const override { this->run(x); }
			virtual void visit(const Char & x)               const override { this->run(x); }
			virtual void visit(const Choose & x)             const override { this->run(x); }
			virtual void visit(const Conditional & x)        const override { this->run(x); }
			virtual void visit(const CustomLiteral & x)      const override { this->run(x); }
			virtual void visit(const Float & x)              const override { this->run(x); }
			virtual void visit(const FxPointer & x)          const override { this->run(x); }
			virtual void visit(const ForwardDynamicCall & x) const override { this->run(x); }
			virtual void visit(const Iife & x)               const override { this->run(x); }
			virtual void visit(const Index & x)              const override { this->run(x); }
			virtual void visit(const Integer & x)            const override { this->run(x); }
			virtual void visit(const InvokeMember & x)       const override { this->run(x); }
			virtual void visit(const Lambda & x)             const override { this->run(x); }
			virtual void visit(const Map & x)                const override { this->run(x); }
			virtual void visit(const Member & x)             const override { this->run(x); }
			virtual void visit(const Null & x)               const override { this->run(x); }
			virtual void visit(const Unary & x)              const override { this->run(x); }
			virtual void visit(const Reflect & x)            const override { this->run(x); }
			virtual void visit(const String & x)             const override { this->run(x); }
			virtual void visit(const Struct & x)             const override { this->run(x); }
			virtual void visit(const Ternary & x)            const override { this->run(x); }
			virtual void visit(const Tuple & x)              const override { this->run(x); }
			virtual void visit(const Type & x)               const override { this->run(x); }
			virtual void visit(const Var & x)                const override { this->run(x); }
		};

		return Visitor{fx}(expr);
	}
}