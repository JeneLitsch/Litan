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



	struct BraceBinding : public Binding {
		BraceBinding()
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



	struct VarBinding : public Binding {
		VarBinding(std::uint64_t addr)
			: Binding {}
			, addr{std::move(addr)} {}
		
		std::uint64_t addr;

		virtual std::size_t alloc_count() const override {
			return 1;
		}
	};



	auto visit_binding(const Binding & binding, auto && fx) {
		if(auto b = as<BraceBinding>(binding)) return fx(*b);
		if(auto b = as<VarBinding>(binding)) return fx(*b);
		throw std::runtime_error{"Unknown SST binding"};
	}
}