#pragma once
#include "ltnc/ast/AST.hxx"
namespace ltn::c {
	template<typename T>
	struct node {
	};

	template<std::integral T>
	struct node<T> {
		using type = sst::Integer;
	};

	template<std::floating_point T>
	struct node<T> {
		using type = sst::Float;
	};

	template<>
	struct node<const std::string> {
		using type = sst::String;
	};
}