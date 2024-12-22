#pragma once
#include <vector>
#include <utility>
#include "ltnvm/Value.hxx"
#include "ltn/reserved_members.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	struct Struct : public Object {
		using Members = std::vector<std::pair<std::uint64_t, Value>>;
		Members members;

		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;

		const Value * get(const auto id) const {
			for(auto & [memberId, member] : this->members) {
				if(id == memberId) {
					return &member;
				}
			}
			return nullptr;
		}

		Value * get(const auto id) {
			for(auto & [memberId, member] : this->members) {
				if(id == memberId) {
					return &member;
				}
			}
			return nullptr;
		}

		virtual Value get_member(std::uint64_t id) const override {
			if(const Value * member = get(id)) {
				return *member;
			}
			else {
				return value::null;
			}
		}
	};




	inline Struct clone(const Struct & strukt) {
		return strukt;
	}
}