#pragma once
#include <string>

namespace ltn::c::compile {
	struct ExprCode {
		std::string code;
		bool assignable;
		bool constant;
	};
}