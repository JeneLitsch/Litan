#include "type_cast.hxx"
#include "ltn/type_code.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/cast.hxx"
#include "ltnvm/objects/type/decode_type.hxx"

namespace ltn::vm {
	namespace {
		template<typename DataType, auto type_check, auto make_value>
		Value cast_unary_type(const std::uint8_t * code, const Value & value, Heap & heap) {
			if(type_check(value)) {
				auto & arr = heap.read<DataType>(value.u);
				DataType result;
				for(const auto & elem : arr) {
					result.push_back(type_cast(std::next(code), elem, heap));
				}
				return make_value(heap.alloc(std::move(result)));
			}
			return value::null;
		}
	}



	struct TypeCast {
		static Value for_any(const std::uint8_t *, const Value & value, Heap &)  {
			return value;
		}

		static Value for_null(const std::uint8_t *, const Value & value, Heap &) {
			return value::null;
		}
		
		static Value for_bool(const std::uint8_t *, const Value & value, Heap &) {
			return value::boolean(cast::to_bool(value));
		}
		
		static Value for_char(const std::uint8_t *, const Value & value, Heap &) {
			return value::character(cast::to_char(value));
		}

		static Value for_int(const std::uint8_t *, const Value & value, Heap &) {
			return value::integer(cast::to_int(value));
		}

		static Value for_float(const std::uint8_t *, const Value & value, Heap & heap) {
			return value::floating(cast::to_float(value, heap));
		}

		static Value for_string(const std::uint8_t *, const Value & value, Heap &  heap) {
			return value::string(heap.alloc(cast::to_string(value, heap)));
		}

		static Value for_array(const std::uint8_t * code, const Value & value, Heap & heap) {
			return cast_unary_type<Array, is_array, value::array>(code, value, heap);
		}

		static Value for_tuple(const std::uint8_t *, const Value & value, Heap & heap) {
			if(is_tuple(value)) {
				return value::tuple(heap.clone<Array>(value.u));
			}
			if(is_array(value)) {
				return value::tuple(heap.clone<Array>(value.u));
			}
			return value::null;
		}

		static Value for_tuple_n(const std::uint8_t * code, const Value & value, Heap & heap) {
			if(is_tuple(value) || is_array(value)) {
				auto & arr = heap.read<Array>(value.u);
				auto size = size_uint_8(code);
				if(size != std::size(arr)) return value::null;
				Array result;
				for(const auto & elem : arr) {
					result.push_back(type_cast(++code, elem, heap));
				}
				return value::tuple(heap.alloc(std::move(result)));
			}
			return value::null;
		}

		static Value for_fx(const std::uint8_t *, const Value & value, Heap & heap) {
			if(is_fxptr(value)) {
				return value;
			}
			return value::null;
		}

		static Value for_fx_n(const std::uint8_t * code, const Value & value, Heap & heap) {
			if(is_fxptr(value)) {
				auto size = size_uint_8(code);
				auto & fx = heap.read<FxPointer>(value.u);
				if(size == fx.params) {
					return value;
				}
			}
			return value::null;
		}

		static Value for_istream(const std::uint8_t *, const Value & value, Heap &) {
			return is_istream(value) ? value : value::null;
		}

		static Value for_ostream(const std::uint8_t *, const Value & value, Heap &) {
			return is_ostream(value) ? value : value::null;
		}

		static Value for_iter(const std::uint8_t *, const Value & value, Heap &) {
			return is_iterator(value) ? value : value::null;
		}

		static Value for_stop(const std::uint8_t *, const Value & value, Heap &) {
			return is_iterator_stop(value) ? value : value::null;
		}

		static Value for_rng(const std::uint8_t *, const Value & value, Heap &) {
			return is_rng(value) ? value : value::null;
		}

		static Value for_type(const std::uint8_t *, const Value & value, Heap &) {
			return is_type(value) ? value : value::null;
		}
		
		static Value for_clock(const std::uint8_t *, const Value & value, Heap &) {
			return is_clock(value) ? value : value::null;
		}

		static Value for_queue(const std::uint8_t * code, const Value & value, Heap & heap) {
			return cast_unary_type<Deque, is_queue, value::queue>(code, value, heap);
		}

		static Value for_stack(const std::uint8_t * code, const Value & value, Heap & heap) {
			return cast_unary_type<Deque, is_stack, value::stack>(code, value, heap);
		}

		static Value for_default(const std::uint8_t *, const Value &, Heap &) {
			return value::null;
		}
	};
	



	Value type_cast(const std::uint8_t * code, const Value & value, Heap & heap) {
		try {
			return decode_type<TypeCast>(code, value, heap);
		}
		catch(...) {
			return value::null;
		} 
	}



	Value type_cast(const Type & type, const Value & value, Heap & heap) {
		return type_cast(type.code.data(), value, heap);
	}
}