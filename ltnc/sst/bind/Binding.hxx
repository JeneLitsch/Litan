#pragma once
#include <vector>
#include <memory>
#include <numeric>
#include "ltn/Visitor.hxx"
#include "ltnc/sst/Node.hxx"
#include "ltnc/sst/types.hxx"

namespace ltn::c::sst::expr {
	struct Expression;
}

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



	struct Group : public Binding {
		Group() : Binding {} {}

		virtual std::size_t alloc_count() const override {
			return std::accumulate(
				std::begin(this->sub_bindings),
				std::end(this->sub_bindings),
				std::size_t{0},
				[] (const auto & curr, const bind_ptr & bind){
					return curr + bind->alloc_count();
				}
			);		
		}

		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<bind_ptr> sub_bindings;
	};

	inline std::unique_ptr<Group> group() {
		return std::make_unique<Group>();
	}



	struct NewVar : public Binding {
		NewVar(std::uint64_t address)
			: Binding {}
			, address{std::move(address)} {}

		virtual std::size_t alloc_count() const override {
			return 1;
		}
		
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::uint64_t address;
	};



	struct Discard : public Binding {
		Discard() : Binding {} {}
		
		virtual std::size_t alloc_count() const override {
			return 0;
		}
	
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}
	};



	struct Global final : public Binding {
		Global(std::uint64_t address)
			: Binding{}
			, address{address} {}

		virtual std::size_t alloc_count() const override { return 0; }
	
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::uint64_t address;
	};



	struct Member final : public Binding {
		Member(
			expr_ptr object,
			std::uint64_t address)
			: Binding{}
			, object{std::move(object)}
			, address{address} {}

		virtual std::size_t alloc_count() const override { return 0; }

		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		expr_ptr object;
		std::uint64_t address;
	};



	struct Local final : public Binding {
		Local(std::uint64_t address)
			: Binding{}
			, address{address} {}

		virtual std::size_t alloc_count() const override { return 0; }
	
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::uint64_t address;
	};



	struct Index final : public Binding {
		Index(expr_ptr range, expr_ptr index)
			: Binding{}
			, range{std::move(range)}
			, index{std::move(index)} {}

		virtual std::size_t alloc_count() const override { return 0; }
	
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		expr_ptr range;
		expr_ptr index;
	};
}