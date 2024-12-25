#pragma once
#include <vector>
#include <memory>
namespace ltn {
	template<class To>
	To * as(auto & from) {
		return dynamic_cast<To*>(&from);
	}

	template<class To>
	const To * as(const auto & from) {
		return dynamic_cast<const To*>(&from);
	}


	template<typename To, typename From>
	bool dynamic_check(const From & from) {
		return dynamic_cast<const To*>(&from);
	}


	template<typename To, typename From>
	bool check_unique(const std::unique_ptr<From> & from) {
		return dynamic_check<To>(*from);
	}
}