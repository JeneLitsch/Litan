#pragma once
#include <functional>
#include <cmath>
#include "litan_compiler/ast/AST.hxx"
#include "to_node_type.hxx"
#include "litan_compiler/sst/expr/Literal.hxx"

namespace ltn::c {
	template<typename Op>
	struct Arithmetic {
		template<sst::expr::literal_type L, sst::expr::literal_type R>
		auto operator()(const L & l, const R & r) const {
			static constexpr Op op;
			using Promoted = decltype(l.value + r.value);
			const auto val_l = static_cast<Promoted>(l.value);
			const auto val_r = static_cast<Promoted>(r.value);
			const auto result = op(val_l, val_r);
			using Node = typename node<decltype(result)>::type;
			return stx::make_unique<Node>(result);
		}
	};


	struct ModuloImpl {
		auto operator()(std::integral auto l, std::integral auto r) const {
			if(r == 0) throw std::runtime_error{""};
			return l % r;
		}

		auto operator()(std::floating_point auto l, std::floating_point auto r) const {
			if(r == 0) throw std::runtime_error{""};
			return std::fmod(l, r);
		}
	};



	struct AdditionImpl {
		auto operator()(auto l, auto r) const {
			return l + r;
		}
	};



	struct SubtractionImpl {
		auto operator()(auto l, auto r) const {
			return l - r;
		}
	};



	struct MultiplyImpl {
		auto operator()(auto l, auto r) const {
			return l * r;
		}
	};



	struct DivideImpl {
		auto operator()(auto l, auto r) const {
			if(r == 0) throw std::runtime_error{""};
			return l / r;
		}
	};



	struct Addition    : Arithmetic<AdditionImpl> {};
	struct Subtraction : Arithmetic<SubtractionImpl> {};
	struct Multiply    : Arithmetic<MultiplyImpl> {};
	struct Divide      : Arithmetic<DivideImpl> {};
	struct Modulo      : Arithmetic<ModuloImpl> {};
}