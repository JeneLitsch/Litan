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

	template<class To>
	To * as(auto & from) {
		return dynamic_cast<To*>(&from);
	}

	template<class To>
	const To * as(const auto & from) {
		return dynamic_cast<const To*>(&from);
	}
}