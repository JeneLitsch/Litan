#include "LtnVM.hxx"

namespace ltn::vm {
	namespace {
		inline Struct & getStruct(const Value ref, Heap & heap) {
			if(isStruct(ref)) {
				return heap.read<Struct>(ref.u);
			}
			else {
				throw except::invalidMemberAccess();
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
			const auto finder = [id] (const auto & pair) {
				return pair.first == id;
			};
			const auto begin = s.members.begin();
			const auto end = s.members.end();
			const auto found = std::find_if(begin, end, finder); 
			s.members.erase(found);
		}
	}

	void LtnVM::member_read() {
		const auto id = this->fetchUint();
		const auto ref = this->reg.pop();
		auto & s = getStruct(ref, this->heap);
		if(const auto * const member = getMember(s, id)) {
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
		auto & s = getStruct(ref, this->heap);
		if(auto * const member = getMember(s, id)) {
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