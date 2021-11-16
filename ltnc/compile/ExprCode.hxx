#pragma once
#include <string>
#include "ltnc/type/Type.hxx"

namespace ltn::c::compile {
	struct ExprCode {
		std::string code;
		bool assignable;
		bool constant;
		type::Type type;
	};
}