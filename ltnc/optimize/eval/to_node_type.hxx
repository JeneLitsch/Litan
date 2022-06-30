#pragma once
#include "ltnc/ast/Ast.hxx"
namespace ltn::c::optimize {
	template<typename T>
	struct node {
	};

	template<std::integral T>
	struct node<T> {
		using type = ast::Integer;
	};

	template<std::floating_point T>
	struct node<T> {
		using type = ast::Float;
	};

	template<>
	struct node<const std::string> {
		using type = ast::String;
	};
}