#pragma once
#include <vector>
#include <utility>
#include "ltnvm/Value.hxx"
#include "ltn/MemberCode.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	struct Struct : public Object {
		using Members = std::vector<std::pair<std::uint64_t, Value>>;
		Members members;

		Value * get(const auto id) {
			for(auto & [memberId, member] : this->members) {
				if(id == memberId) {
					return &member;
				}
			}
			return nullptr;
		}
	};




	inline Struct clone(const Struct & strukt) {
		return strukt;
	}
}