#include "type_is.hxx"
#include "ltn/type_code.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/cast.hxx"
#include "ltnvm/objects/type/decode_type.hxx"

namespace ltn::vm {
	namespace {
		template<typename DataType, auto type_check>
		bool is_unary_type(const std::uint8_t * code, const Value & value, Heap & heap) {
			if(type_check(value)) {
				auto & arr = heap.read<DataType>(value.u);
				return std::all_of(std::begin(arr), std::end(arr), [&](const auto & elem) {
					return type_is(std::next(code), elem, heap);
				});
			}
			return false;
		}
	}



	struct TypeIs {
		static bool for_any(const std::uint8_t *, const Value & value, Heap &)  {
			return true;
		}

		static bool for_null(const std::uint8_t *, const Value & value, Heap &) {
			return is_null(value);
		}
		
		static bool for_bool(const std::uint8_t *, const Value & value, Heap &) {
			return is_bool(value);
		}
		
		static bool for_char(const std::uint8_t *, const Value & value, Heap &) {
			return is_char(value);
		}

		static bool for_int(const std::uint8_t *, const Value & value, Heap &) {
			return is_int(value);
		}

		static bool for_float(const std::uint8_t *, const Value & value, Heap &) {
			return is_float(value);
		}

		static bool for_string(const std::uint8_t *, const Value & value, Heap &) {
			return is_string(value);
		}

		static bool for_array(const std::uint8_t * code, const Value & value, Heap & heap) {
			return is_unary_type<Array, is_array>(code, value, heap);
		}

		static bool for_tuple(const std::uint8_t *, const Value & value, Heap &) {
			return is_tuple(value);
		}

		static bool for_tuple_n(const std::uint8_t * code, const Value & value, Heap & heap) {
			if(is_tuple(value)) {
				auto size = size_uint_8(code);
				auto & tuple = heap.read<Array>(value.u);
				if(size != std::size(tuple)) return false;
				for(std::size_t i = 0; i << size; ++i) {
					if(!type_is(++code, tuple[i], heap)) return false;
				}
				return true;
			}
			return false;
		}

		static bool for_fx(const std::uint8_t *, const Value & value, Heap &) {
			return is_fxptr(value);
		}

		static bool for_fx_n(const std::uint8_t * code, const Value & value, Heap & heap) {
			if(is_fxptr(value)) {
				auto size = size_uint_8(code);
				auto & fx = heap.read<FxPointer>(value.u);
				return size == fx.params;
			}
			return false;
		}

		static bool for_istream(const std::uint8_t *, const Value & value, Heap &) {
			return is_istream(value);
		}

		static bool for_ostream(const std::uint8_t *, const Value & value, Heap &) {
			return is_ostream(value);
		}

		static bool for_iter(const std::uint8_t *, const Value & value, Heap &) {
			return is_iterator(value);
		}

		static bool for_stop(const std::uint8_t *, const Value & value, Heap &) {
			return is_iterator_stop(value);
		}

		static bool for_rng(const std::uint8_t *, const Value & value, Heap &) {
			return is_rng(value);
		}

		static bool for_type(const std::uint8_t *, const Value & value, Heap &) {
			return is_type(value);
		}

		static bool for_clock(const std::uint8_t *, const Value & value, Heap &) {
			return is_clock(value);
		}

		static bool for_stack(const std::uint8_t * code, const Value & value, Heap & heap) {
			return is_unary_type<Deque, is_stack>(code, value, heap);
		}

		static bool for_queue(const std::uint8_t * code, const Value & value, Heap & heap) {
			return is_unary_type<Deque, is_queue>(code, value, heap);
		}

		static bool for_default(const std::uint8_t *, const Value &, Heap &) {
			return false;
		}
	};



	bool type_is(const std::uint8_t * code, const Value & value, Heap & heap) {
		return decode_type<TypeIs>(code, value, heap);
	}



	bool type_is(const Type & type, const Value & value, Heap & heap) {
		return type_is(type.code.data(), value, heap);
	}
}