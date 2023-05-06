#include "Type.hxx"
#include "ltn/type_code.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/cast.hxx"

namespace ltn::vm {
	namespace {
		std::uint64_t tuple_size(const std::uint8_t *& code) {
			std::uint64_t size = 0;
			for(std::size_t i = 0; i < 8; ++i) {
				size += static_cast<std::uint64_t>(*(++code)) << (i * 8);
			}
			return size;
		}
		void decode_tuple(const std::uint8_t * code, auto fx) {
			auto size = tuple_size(code);
			for(std::size_t i = 0; i < size; ++i) {
				fx(++code);
			}
		}
	}


	template<typename Op, typename ... Args>
	auto decode_type(const std::uint8_t * code, Args && ...args) {
		switch (*code) {
			case type_code::ANY: return Op::for_any(code, args...);
			case type_code::NVLL: return Op::for_null(code, args...);
			case type_code::BOOL: return Op::for_bool(code, args...);
			case type_code::CHAR: return Op::for_char(code, args...);
			case type_code::INT: return Op::for_int(code, args...);
			case type_code::FLOAT: return Op::for_float(code, args...);
			case type_code::STRING: return Op::for_string(code, args...);
			case type_code::ARRAY: return Op::for_array(code, args...);
			case type_code::TUPLE: return Op::for_tuple(code, args...);
			case type_code::TUPLE_N: return Op::for_tuple_n(code, args...);
			default: return Op::for_default(code, args...);
		}
	}



	struct TypeName {
		static std::string for_any(const std::uint8_t *)  {
			return "...";
		}

		static std::string for_null(const std::uint8_t *) {
			return "null";
		}
		
		static std::string for_bool(const std::uint8_t *) {
			return "bool";
		}
		
		static std::string for_char(const std::uint8_t *) {
			return "char";
		}

		static std::string for_int(const std::uint8_t *) {
			return "int";
		}

		static std::string for_float(const std::uint8_t *) {
			return "float";
		}

		static std::string for_string(const std::uint8_t *) {
			return "string";
		}

		static std::string for_array(const std::uint8_t * code) {
			return "array(" + to_type_name(std::next(code)) + ")";
		}

		static std::string for_tuple(const std::uint8_t *) {
			return "tuple";
		}

		static std::string for_tuple_n(const std::uint8_t * code) {
			std::ostringstream oss;
			oss << "tuple(";
			decode_tuple(code, [&] (auto * elem) { oss << to_type_name(elem); });
			oss << ")";
			return oss.str();
		}

		static std::string for_default(const std::uint8_t *) {
			throw except::invalid_argument("Cannot generate type name");
		}
	};



	std::string to_type_name(const std::uint8_t * code) {
		return decode_type<TypeName>(code);
	}



	std::string to_type_name(const Type & type) {
		return to_type_name(type.code.data());	
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
			if(is_array(value)) {
				auto & arr = heap.read<Array>(value.u);
				return std::all_of(std::begin(arr), std::end(arr), [&](const auto & elem) {
					return type_is(std::next(code), elem, heap);
				});
			}
			return false;
		}

		static bool for_tuple(const std::uint8_t *, const Value & value, Heap &) {
			return is_tuple(value);
		}

		static bool for_tuple_n(const std::uint8_t * code, const Value & value, Heap & heap) {
			if(is_tuple(value)) {
				auto size = tuple_size(code);
				auto & tuple = heap.read<Array>(value.u);
				if(size != std::size(tuple)) return false;
				for(std::size_t i = 0; i << size; ++i) {
					if(!type_is(++code, tuple[i], heap)) return false;
				}
				return true;
			}
			return false;
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
			if(is_array(value)) {
				auto & arr = heap.read<Array>(value.u);
				Array result;
				for(const auto & elem : arr) {
					result.push_back(type_cast(std::next(code), elem, heap));
				}
				return value::array(heap.alloc(std::move(result)));
			}
			return value::null;
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
				auto size = tuple_size(code);
				if(size != std::size(arr)) return value::null;
				Array result;
				for(const auto & elem : arr) {
					result.push_back(type_cast(++code, elem, heap));
				}
				return value::tuple(heap.alloc(std::move(result)));
			}
			return value::null;
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