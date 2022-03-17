#pragma once
#include <vector>
namespace ltn::c::compile {
	template<class To>
	To * as(auto & from) {
		return dynamic_cast<To*>(&from);
	}

	template<class To>
	const To * as(const auto & from) {
		return dynamic_cast<const To*>(&from);
	}
}