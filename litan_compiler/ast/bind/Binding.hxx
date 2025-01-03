#pragma once
#include <vector>
#include <memory>
#include "litan_core/Visitor.hxx"
#include "litan_compiler/ast/Node.hxx"
#include "litan_compiler/ast/types.hxx"

namespace ltn::c::ast::bind {
	struct Group;
	struct NewVar;


	
	using BindVisitor = Visitor<Group, NewVar>;



	struct Binding : public Node {
		Binding(const SourceLocation & location)
			: Node {location} {}

		virtual void accept(const BindVisitor &) const = 0;
	};



	auto visit(const Binding & binding, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, Group>;
		using Base = FunctionVisitor<BindVisitor, Callable, Ret>;
		
		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 
			virtual void visit(const Group & x)  const override { this->run(x); };
			virtual void visit(const NewVar & x) const override { this->run(x); };
		};

		return Visitor{fx}(binding);
	}
}