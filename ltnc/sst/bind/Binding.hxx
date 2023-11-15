#pragma once
#include <vector>
#include <memory>
#include <numeric>
#include "ltn/Visitor.hxx"
#include "ltnc/sst/Node.hxx"
#include "ltnc/sst/types.hxx"

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
}