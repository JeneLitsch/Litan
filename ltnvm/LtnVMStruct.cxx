#include "LtnVM.hxx"

namespace ltn::vm {
	Struct & getStruct(const Value & ref, Heap & heap) {
		if(isStruct(ref)) {
			return heap.read<Struct>(ref.u);
		}
		else {
			throw std::runtime_error {
				"Cannot access member of non-struct type"};
		}
	}

	Value * getMember(Struct & s, const auto id) {
		for(auto & [memberId, member] : s.members) {
			if(id == memberId) {
				return &member;
			}
		}
		return nullptr;
	}

	void deleteMember(Struct & s, const auto id) {
		const auto finder = [&] (const auto & pair) {
			return pair.first == id;
		};
		auto found = std::find_if(s.members.begin(), s.members.end(), finder); 
		s.members.erase(found);
	}

	void LtnVM::member_read() {
		const auto id = this->fetchUint();
		const auto ref = this->reg.pop();
		auto & s = heap.read<Struct>(ref.u);
		if(const auto * member = getMember(s, id)) {
			this->reg.push(*member);
		}
		else {
			this->reg.push(value::null);
		}
	}
	
	void LtnVM::member_write() {
		const auto id = this->fetchUint();
		const auto ref = this->reg.pop();
		const auto value = this->reg.pop();
		auto & s = heap.read<Struct>(ref.u);
		if(auto * member = getMember(s, id)) {
			if(isNull(value)) {
				deleteMember(s, id);
			}
			else {
				(*member) = value;
			}
		}
		else {
			s.members.push_back({id, value});
		}
	}

}