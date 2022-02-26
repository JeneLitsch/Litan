#pragma once
#include <vector>
#include <string>
namespace ltn::c::ast {
	using Namespace = std::vector<std::string>;
	bool is_absolute(const Namespace & ns);
}