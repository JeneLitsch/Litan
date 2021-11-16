#pragma once
#include <vector>
#include "ltnc/type/Type.hxx"
namespace ltn::c::compile {
	inline auto toTypes(const auto & parameters) {
		std::vector<ltn::c::type::Type> types;
		for(const auto [type, name] : parameters) {
			types.push_back(type);
		}
		return types;
	}
}