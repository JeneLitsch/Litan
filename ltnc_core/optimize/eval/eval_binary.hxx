#pragma once
#include <functional>
#include "ltnc_core/ast/Ast.hxx"
#include "to_node_type.hxx"
namespace ltn::c::optimize {
	template<typename Op>
	struct Arithmetic {
		template<ast::literal_type L, ast::literal_type R>
		auto operator()(const L & l, const R & r) const {
			static constexpr Op op;
			using Promoted = decltype(l.value + r.value);
			const auto val_l = static_cast<Promoted>(l.value);
			const auto val_r = static_cast<Promoted>(r.value);
			const auto result = op(val_l, val_r);
			using Node = typename node<decltype(result)>::type;
			return std::make_unique<Node>(result, l.location);
		}
	};

	struct Addition    : Arithmetic<std::plus<void>> {};
	struct Subtraction : Arithmetic<std::minus<void>> {};
	struct Multiply    : Arithmetic<std::multiplies<void>> {};
	struct Divide      : Arithmetic<std::divides<void>> {};
}