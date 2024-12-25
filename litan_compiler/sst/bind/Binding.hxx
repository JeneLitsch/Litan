#pragma once
#include <vector>
#include <memory>
#include <numeric>
#include "litan_core/Visitor.hxx"
#include "litan_compiler/sst/Node.hxx"
#include "litan_compiler/sst/types.hxx"

namespace ltn::c::sst::bind {
	
	struct Group;
	struct NewVar;
	struct Discard;
	struct Global;
	struct Member;
	struct Local;
	struct Index;

	
	
	using BindVisitor = Visitor<
		Group,
		NewVar,
		Discard,
		Global,
		Member,
		Local,
		Index
	>;



	struct Binding : public Node {
		Binding() : Node {} {}

		virtual std::size_t alloc_count() const = 0;
	
		virtual void accept(const BindVisitor &) const = 0;
	};



	template<typename Derived>
	struct BindingCRTP : Binding {
		virtual void accept(const BindVisitor & visitor) const override {
			return visitor.visit(static_cast<const Derived &>(*this));
		}
	};



	auto visit(const Binding & binding, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, Discard>;
		using Base = FunctionVisitor<BindVisitor, Callable, Ret>;
		
		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 
			
			virtual void visit(const Group & x)   const override { this->run(x); };
			virtual void visit(const NewVar & x)  const override { this->run(x); };
			virtual void visit(const Discard & x) const override { this->run(x); };
			virtual void visit(const Global & x)  const override { this->run(x); };
			virtual void visit(const Member & x)  const override { this->run(x); };
			virtual void visit(const Local & x)   const override { this->run(x); };
			virtual void visit(const Index & x)   const override { this->run(x); };
		};

		return Visitor{fx}(binding);
	}
}