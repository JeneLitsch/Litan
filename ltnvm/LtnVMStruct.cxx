#include "LtnVM.hxx"

namespace ltn::vm {
	namespace {
		inline Struct & get_struct(const Value ref, Heap & heap) {
			if(is_struct(ref)) {
				return heap.read<Struct>(ref.u);
			}
			else {
				throw except::invalid_member_access();
			}
		}

		Value * get_member(Struct & s, const auto id) {
			for(auto & [memberId, member] : s.members) {
				if(id == memberId) {
					return &member;
				}
			}
			return nullptr;
		}

		void delete_member(Struct & s, const auto id) {			
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
		const auto id = this->fetch_uint();
		const auto ref = this->core.reg.pop();
		auto & s = get_struct(ref, this->core.heap);
		if(const auto * const member = get_member(s, id)) {
			this->core.reg.push(*member);
		}
		else {
			this->core.reg.push(value::null);
		}
	}
	
	void LtnVM::member_write() {
		const auto id = this->fetch_uint();
		const auto ref = this->core.reg.pop();
		const auto value = this->core.reg.pop();
		auto & s = get_struct(ref, this->core.heap);
		if(auto * const member = get_member(s, id)) {
			if(is_null(value)) {
				delete_member(s, id);
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