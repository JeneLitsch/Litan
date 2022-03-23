#pragma once
#include <concepts>
#include "ltnc_core/ast/Ast.hxx"

namespace ltn::c::optimize {
	template<typename T>
	concept literal_type = std::is_base_of<ast::Literal, T>::value;
}