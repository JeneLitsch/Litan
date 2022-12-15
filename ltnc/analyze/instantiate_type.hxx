#pragma once
#include <span>
#include "ltnc/type/Type.hxx"
#include "utils/Scope.hxx"

namespace ltn::c {
	type::Type instantiate_type(
		const type::IncompleteType & incomplete,
		const Scope & scope);
}