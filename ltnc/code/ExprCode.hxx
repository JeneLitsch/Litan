#pragma once
#include <string>
namespace ltn::c::assembly {
	struct ExprCode {
	public:
		std::string code;
		bool assignable;
		bool constant;
	};
};