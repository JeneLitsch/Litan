#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		inline Struct & get_struct(const Value ref, Heap & heap) {
			if(is_struct(ref)) {
				return heap.read<Struct>(ref);
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



	void member_read(VmCore & core) {
		const auto id = core.fetch_uint();
		const auto ref = core.stack.pop();
		auto & s = get_struct(ref, core.heap);
		if(const auto * const member = get_member(s, id)) {
			core.stack.push(*member);
		}
		else {
			core.stack.push(value::null);
		}
	}
	

	
	void member_write(VmCore & core) {
		const auto id = core.fetch_uint();
		const auto ref = core.stack.pop();
		const auto value = core.stack.pop();
		auto & s = get_struct(ref, core.heap);
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