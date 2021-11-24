#pragma once
#include <vector>
#include <string>
namespace ltn::c::ast {
	using Namespace = std::vector<std::string>;

	bool match(
		const Namespace & full,
		const Namespace & from,
		const Namespace & to);
}