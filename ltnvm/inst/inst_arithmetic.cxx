#include "instructions.hxx"
#include "stdxx/string.hxx"
#include "stdxx/array.hxx"
#include <cmath>
#include "ltnvm/utils/type_check.hxx"
#include <sstream>
#include "ltnvm/Operations.hxx"
#include "ltnvm/calcBinary.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/utils/cast.hxx"
#include "ltnvm/utils/special_member.hxx"

#define FETCH\
	const auto r = core.stack.pop();\
	const auto l = core.stack.pop();

namespace ltn::vm::inst {
	namespace {
		template<typename T>
		std::uint64_t concat(const Value & l, const Value & r, Heap & heap) {
			const auto obj_l = heap.read<T>(l.u);
			const auto obj_r = heap.read<T>(r.u);
			return heap.alloc<T>({obj_l + obj_r});
		} 



		template<typename Container>
		std::uint64_t repeat(
			const Value & ref,
			const Value & repetitions,
			Heap & heap) {
			
			const auto & str = heap.read<Container>(ref.u);
			const auto & count = cast::to_int(repetitions);
			auto repeated = stx::repeat(str, count);
			const auto ptr = heap.alloc<Container>(std::move(repeated)); 
			return ptr;
		}
	}



	void add(VmCore & core) {
		FETCH

		if(is_array(l) && is_array(r)) {
			return core.stack.push(value::array(concat<Array>(l,r,core.heap)));
		}

		if(is_tuple(l) && is_tuple(r)) {
			return core.stack.push(value::tuple(concat<Array>(l,r,core.heap)));
		}

		if(is_string(l) && is_string(r)) {
			return core.stack.push(value::string(concat<String>(l,r,core.heap)));
		}

		if(is_struct(l)) {
			return core.stack.push(call_special_member<MemberCode::ADD>(core, l, r));
		}

		core.stack.push(calc<Addition>(l, r));
	}



	void sub(VmCore & core) {
		FETCH

		if(is_struct(l)) {
			return core.stack.push(call_special_member<MemberCode::SUB>(core, l, r));
		}

		core.stack.push(calc<Subtraction>(l, r));
	}



	void mlt(VmCore & core) {
		FETCH

		if(is_string(l) && is_integral(r)) {
			return core.stack.push(value::string(repeat<String>(l, r, core.heap)));
		}

		if(is_integral(l) && is_string(r)) {
			return core.stack.push(value::string(repeat<String>(r, l, core.heap)));
		}

		if(is_array(l) && is_integral(r)) {
			return core.stack.push(value::array(repeat<Array>(l, r, core.heap)));
		}

		if(is_integral(l) && is_array(r)) {
			return core.stack.push(value::array(repeat<Array>(r, l, core.heap)));
		}

		if(is_struct(l)) {
			return core.stack.push(call_special_member<MemberCode::MLT>(core, l, r));
		}

		core.stack.push(calc<Multiplication>(l, r));
	}



	void div(VmCore & core) {
		FETCH

		if(is_struct(l)) {
			return core.stack.push(call_special_member<MemberCode::DIV>(core, l, r));
		}

		core.stack.push(calc<Division>(l, r));
	}



	void mod(VmCore & core) {
		FETCH

		if(is_struct(l)) {
			return core.stack.push(call_special_member<MemberCode::MOD>(core, l, r));
		}
		
		core.stack.push(calc<Modulo>(l, r));
	}



	void pow(VmCore & core) {
		FETCH

		if(is_struct(l)) {
			return core.stack.push(call_special_member<MemberCode::POW>(core, l, r));
		}

		core.stack.push(calc<Power>(l, r));
	}
}
#undef FETCH