#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		inline Struct & get_struct(const Value ref, Heap & heap) {
			if(is_struct(ref)) {
				return heap.read<Struct>(ref.u);
			}
			else {
				throw except::invalid_member_access();
			}
		}




		void delete_member(Struct & strukt, const auto id) {			
			const auto finder = [id] (const auto & pair) {
				return pair.first == id;
			};
			const auto begin = strukt.members.begin();
			const auto end = strukt.members.end();
			const auto found = std::find_if(begin, end, finder); 
			strukt.members.erase(found);
		}
	}



	void member_read(VmCore & core) {
		const auto id = core.fetch_uint();
		const auto ref = core.stack.pop();
		auto & strukt = get_struct(ref, core.heap);
		if(const auto * const member = strukt.get(id)) {
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
		auto & strukt = get_struct(ref, core.heap);
		if(auto * const member = strukt.get(id)) {
			if(is_null(value)) {
				delete_member(strukt, id);
			}
			else {
				(*member) = value;
			}
		}
		else {
			strukt.members.push_back({id, value});
		}
	}
}