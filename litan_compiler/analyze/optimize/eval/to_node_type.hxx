#pragma once
#include "litan_compiler/ast/AST.hxx"
namespace ltn::c {
	template<typename T>
	struct node {
	};

	template<std::integral T>
	struct node<T> {
		using type = sst::expr::Integer;
	};

	template<std::floating_point T>
	struct node<T> {
		using type = sst::expr::Float;
	};

	template<>
	struct node<const std::string> {
		using type = sst::expr::String;
	};
}