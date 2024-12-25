#include "instructions.hxx"
#include "stdxx/string.hxx"
#include "stdxx/array.hxx"
#include <cmath>
#include "litan_vm/utils/type_check.hxx"
#include <sstream>
#include "litan_vm/utils/calc_binary.hxx"
#include "litan_vm/utils/convert.hxx"
#include "litan_vm/utils/cast.hxx"
#include "litan_vm/utils/special_member.hxx"

#define FETCH\
	const auto r = core.stack.pop();\
	const auto l = core.stack.pop();


namespace ltn::vm::inst {
	namespace {
		template<typename T>
		T * concat(const Value & l, const Value & r, Heap & heap) {
			const T * obj_l = value::as<T>(l);
			const T * obj_r = value::as<T>(r);
			return heap.alloc<T>({obj_l->get_underlying() + obj_r->get_underlying()});
		} 



		String * concat_string(const Value & l, const Value & r, Heap & heap) {
			const String * obj_l = value::as<String>(l);
			const String * obj_r = value::as<String>(r);
			return heap.alloc<String>({obj_l->copy_to_std_string() + obj_r->copy_to_std_string()});
		} 



		template<typename T>
		T * repeat(
			const Value & ref,
			const Value & repetitions,
			Heap & heap) {
			
			const auto & str = *value::as<T>(ref);
			const auto & count = cast::to_int(repetitions);
			auto repeated = stx::repeat(str.get_underlying(), count);
			const auto ptr = heap.alloc(T{std::move(repeated)}); 
			return ptr;
		}



		String * repeat_string(
			const Value & ref,
			const Value & repetitions,
			Heap & heap) {
			
			const auto & str = *value::as<String>(ref);
			const auto & count = cast::to_int(repetitions);
			std::ostringstream oss;
			for(std::int64_t i = 0; i < count; i++) {
				oss << static_cast<std::string_view>(str);
			}
			const auto ptr = heap.alloc(String{oss.str()}); 
			return ptr;
		}


				// Promotes operands to at least int64
		// Bool --> Int -?> Double
		template<class Op>
		struct Promoted {
			constexpr inline auto operator()(const auto l, const auto r) const {
				constexpr Op op{};
				using T = decltype(l+r+std::int64_t(1));
				return op(static_cast<T>(l), static_cast<T>(r));
			}
		};

		using Addition = Promoted<std::plus<void>>;
		using Subtraction = Promoted<std::minus<void>>;
		using Multiplication = Promoted<std::multiplies<void>>;



		struct Division {
			constexpr auto operator()(const auto l, const auto r) const {
				if(r == 0) throw except::division_by_zero();
				using T = decltype(l+r+std::int64_t(1));
				return static_cast<T>(l) / static_cast<T>(r);
			}
		};

		
		
		struct Modulo {
			constexpr auto operator()(const auto l, const auto r) const {
				if(r == 0) throw except::division_by_zero();
				using T = decltype(l+r+std::int64_t(1));
				if constexpr(std::integral<T>) {
					return static_cast<std::int64_t>(l%r);
				}
				else {
					return std::fmod(l, r);
				}
			}
		};



		struct Power {
			constexpr auto operator()(const auto l, const auto r) const 
				-> decltype(l+r+std::int64_t(1)) {
				
				using T = decltype(l+r+std::int64_t(1));
				return static_cast<T>(std::pow(static_cast<T>(l), static_cast<T>(r)));
			}
		};
	}



	void add(VMCore & core) {
		FETCH

		if(is_array(l) && is_array(r)) {
			return core.stack.push(value::array(concat<Array>(l,r,core.heap)));
		}

		if(is_tuple(l) && is_tuple(r)) {
			return core.stack.push(value::tuple(concat<Tuple>(l,r,core.heap)));
		}

		if(is_string(l) && is_string(r)) {
			return core.stack.push(value::string(concat_string(l,r,core.heap)));
		}

		if(is_struct(l)) {
			return core.stack.push(call_special_member<ReservedMemberCode::OPERATOR_ADD>(core, l, r));
		}

		core.stack.push(calc<Addition>(l, r));
	}



	void sub(VMCore & core) {
		FETCH

		if(is_struct(l)) {
			return core.stack.push(call_special_member<ReservedMemberCode::OPERATOR_SUB>(core, l, r));
		}

		core.stack.push(calc<Subtraction>(l, r));
	}



	void mlt(VMCore & core) {
		FETCH

		if(is_string(l) && is_integral(r)) {
			return core.stack.push(value::string(repeat_string(l, r, core.heap)));
		}

		if(is_integral(l) && is_string(r)) {
			return core.stack.push(value::string(repeat_string(r, l, core.heap)));
		}

		if(is_array(l) && is_integral(r)) {
			return core.stack.push(value::array(repeat<Array>(l, r, core.heap)));
		}

		if(is_integral(l) && is_array(r)) {
			return core.stack.push(value::array(repeat<Array>(r, l, core.heap)));
		}

		if(is_struct(l)) {
			return core.stack.push(call_special_member<ReservedMemberCode::OPERATOR_MLT>(core, l, r));
		}

		core.stack.push(calc<Multiplication>(l, r));
	}



	void div(VMCore & core) {
		FETCH

		if(is_struct(l)) {
			return core.stack.push(call_special_member<ReservedMemberCode::OPERATOR_DIV>(core, l, r));
		}

		core.stack.push(calc<Division>(l, r));
	}



	void mod(VMCore & core) {
		FETCH

		if(is_struct(l)) {
			return core.stack.push(call_special_member<ReservedMemberCode::OPERATOR_MOD>(core, l, r));
		}
		
		core.stack.push(calc<Modulo>(l, r));
	}



	void pow(VMCore & core) {
		FETCH

		if(is_struct(l)) {
			return core.stack.push(call_special_member<ReservedMemberCode::OPERATOR_POW>(core, l, r));
		}

		core.stack.push(calc<Power>(l, r));
	}
}
#undef FETCH