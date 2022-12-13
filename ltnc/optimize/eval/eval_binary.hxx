#pragma once
#include <functional>
#include <cmath>
#include "ltnc/ast/AST.hxx"
#include "to_node_type.hxx"
namespace ltn::c {
	template<typename Op>
	struct Arithmetic {
		template<sst::literal_type L, sst::literal_type R>
		auto operator()(const L & l, const R & r) const {
			static constexpr Op op;
			using Promoted = decltype(l.value + r.value);
			const auto val_l = static_cast<Promoted>(l.value);
			const auto val_r = static_cast<Promoted>(r.value);
			const auto result = op(val_l, val_r);
			using Node = typename node<decltype(result)>::type;
			return stx::make_unique<Node>(result, l.location);
		}
	};


	struct modolus {
		auto operator()(std::integral auto l, std::integral auto r) const {
			return l % r;
		}

		auto operator()(std::floating_point auto l, std::floating_point auto r) const {
			return std::fmod(l, r);
		}
	};


	struct Addition    : Arithmetic<std::plus<void>> {};
	struct Subtraction : Arithmetic<std::minus<void>> {};
	struct Multiply    : Arithmetic<std::multiplies<void>> {};
	struct Divide      : Arithmetic<std::divides<void>> {};
	struct Modulo      : Arithmetic<modolus> {};
}