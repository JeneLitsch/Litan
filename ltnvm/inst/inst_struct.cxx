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



		void delete_member(Struct & strukt, const auto id) {			
			const auto finder = [id] (const auto & pair) {
				return pair.first == id;
			};
			const auto begin = strukt.members.begin();
			const auto end = strukt.members.end();
			const auto found = std::find_if(begin, end, finder); 
			strukt.members.erase(found);
		}



		// void read_struct_member(VMCore & core, const Value & ref, std::uint64_t id) {
		// 	Struct * strukt = ref.as<Struct>();
		// 	if(const Value * const member = strukt->get(id)) {
		// 		return core.stack.push(*member);
		// 	}
		// 	else {
		// 		return core.stack.push(value::null);
		// 	}
		// }



		// void read_array_member(VMCore & core, const Value & ref, std::uint64_t id) {
		// 	if(id == static_cast<std::uint64_t>(MemberCode::SIZE)) {
		// 		NativeFunctionPointer * function_pointer = core.heap.alloc(NativeFunctionPointer(, 1, false));
		// 		core.stack.push(value::native_function(function_pointer));
		// 	}
		// }
	}



	void member_read(VMCore & core) {
		const auto id = core.fetch_uint();
		const auto ref = core.stack.pop();
		if(is_object(ref)) {
			core.stack.push(ref.as<Object>()->get_member(id));
			return;
		}
		// if(is_object(ref)) {
		// 	return read_struct_member(core, ref, id);
		// }
		// if(is_array(ref)) {
		// 	return read_array_member(core, ref, id);
		// }
		throw except::invalid_member_access();
	}
	

	
	void member_write(VMCore & core) {
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