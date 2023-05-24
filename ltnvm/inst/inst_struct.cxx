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



		Value * get_member(Struct & strukt, const auto id) {
			for(auto & [memberId, member] : strukt.members) {
				if(id == memberId) {
					return &member;
				}
			}
			return nullptr;
		}



		Value * get_operator(Struct & strukt, const auto id) {
			for(auto & [opId, op] : strukt.operators) {
				if(id == opId) {
					return &op;
				}
			}
			return nullptr;
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



		void delete_operator(Struct & strukt, const auto id) {			
			const auto finder = [id] (const auto & pair) {
				return pair.first == id;
			};
			const auto begin = strukt.operators.begin();
			const auto end = strukt.operators.end();
			const auto found = std::find_if(begin, end, finder); 
			strukt.operators.erase(found);
		}
	}



	void member_read(VmCore & core) {
		const auto id = core.fetch_uint();
		const auto ref = core.stack.pop();
		auto & strukt = get_struct(ref, core.heap);
		if(const auto * const member = get_member(strukt, id)) {
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
		if(auto * const member = get_member(strukt, id)) {
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


	void operator_write(VmCore & core) {
		const auto id = static_cast<OperatorCode>(core.fetch_byte());
		const auto ref = core.stack.pop();
		const auto value = core.stack.pop();
		auto & strukt = get_struct(ref, core.heap);
		if(auto * const op = get_operator(strukt, id)) {
			if(is_null(value)) {
				delete_operator(strukt, id);
			}
			else {
				(*op) = value;
			}
		}
		else {
			strukt.operators.push_back({id, value});
		}
	}
}