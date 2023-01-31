#pragma once
#include "Node.hxx"
#include <vector>
#include <memory>
#include <numeric>

namespace ltn::c::sst {
	struct Binding : public Node {
		Binding() : Node {} {}

		virtual std::size_t alloc_count() const = 0;
	};



	struct GroupBinding : public Binding {
		GroupBinding()
			: Binding {} {}
		
		std::vector<std::unique_ptr<Binding>> sub_bindings;

		virtual std::size_t alloc_count() const override {
			return std::accumulate(
				std::begin(this->sub_bindings),
				std::end(this->sub_bindings),
				std::size_t{0},
				[] (const auto & curr, const std::unique_ptr<Binding> & bind){
					return curr + bind->alloc_count();
				}
			);		
		}
	};



	struct NewVarBinding : public Binding {
		NewVarBinding(std::uint64_t addr)
			: Binding {}
			, addr{std::move(addr)} {}
		
		std::uint64_t addr;

		virtual std::size_t alloc_count() const override {
			return 1;
		}
	};



	struct NoBinding : public Binding {
		NoBinding() : Binding {} {}
		
		virtual std::size_t alloc_count() const override {
			return 0;
		}
	};



	struct GlobalBinding final : public Binding {
		GlobalBinding(std::uint64_t addr)
			: Binding{}
			, addr{addr} {}
		virtual ~GlobalBinding() = default;
		std::uint64_t addr;

		virtual std::size_t alloc_count() const override { return 0; }
	};



	struct MemberBinding final : public Binding {
		MemberBinding(
			std::unique_ptr<Expression> object,
			std::uint64_t addr)
			: Binding{}
			, object{std::move(object)}
			, addr{addr} {}
		virtual ~MemberBinding() = default;
		std::unique_ptr<Expression> object;
		std::uint64_t addr;

		virtual std::size_t alloc_count() const override { return 0; }

	};



	struct LocalBinding final : public Binding {
		LocalBinding(
			std::uint64_t addr)
			: Binding{}
			, addr{addr} {}
		virtual ~LocalBinding() = default;
		std::uint64_t addr;

		virtual std::size_t alloc_count() const override { return 0; }
	};



	struct IndexBinding final : public Binding {
		IndexBinding(
			std::unique_ptr<Expression> range,
			std::unique_ptr<Expression> index)
			: Binding{}
			, range{std::move(range)}
			, index{std::move(index)} {}
		virtual ~IndexBinding() = default;
		std::unique_ptr<Expression> range;
		std::unique_ptr<Expression> index;

		virtual std::size_t alloc_count() const override { return 0; }
	};



	auto visit_binding(const Binding & binding, auto && fx) {
		if(auto b = as<GroupBinding>(binding))  return fx(*b);
		if(auto b = as<NewVarBinding>(binding)) return fx(*b);
		if(auto b = as<NoBinding>(binding))     return fx(*b);
		if(auto b = as<GlobalBinding>(binding)) return fx(*b);
		if(auto b = as<MemberBinding>(binding)) return fx(*b);
		if(auto b = as<LocalBinding>(binding))  return fx(*b);
		if(auto b = as<IndexBinding>(binding))  return fx(*b);
		throw std::runtime_error{"Unknown SST binding"};
	}
}