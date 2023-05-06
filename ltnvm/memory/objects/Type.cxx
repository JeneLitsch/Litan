#include "Type.hxx"
#include "ltn/type_code.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/cast.hxx"

namespace ltn::vm {
	std::string to_type_name(const std::uint8_t * code) {
		switch (*code) {
		case type_code::ANY: return "...";
		case type_code::NVLL: return "null";
		case type_code::BOOL: return "bool";
		case type_code::CHAR: return "char";
		case type_code::INT: return "int";
		case type_code::FLOAT: return "float";
		case type_code::STRING: return "string";
		case type_code::ARRAY: return "array(" + to_type_name(std::next(code)) + ")";
		}
		throw except::invalid_argument("Cannot generate type name");
	}



	std::string to_type_name(const Type & type) {
		return to_type_name(type.code.data());	
	}



	bool type_is(const std::uint8_t * code, const Value & value, Heap & heap) {
		switch (*code) {
		case type_code::ANY: return true;
		case type_code::NVLL: return is_null(value);
		case type_code::BOOL: return is_bool(value);
		case type_code::CHAR: return is_char(value);
		case type_code::INT: return is_int(value);
		case type_code::FLOAT: return is_float(value);
		case type_code::STRING: return is_string(value);
		case type_code::ARRAY: {
			if(is_array(value)) {
				auto & arr = heap.read<Array>(value.u);
				return std::all_of(std::begin(arr), std::end(arr), [&](const auto & elem) {
					return type_is(std::next(code), elem, heap);
				});
			}
		}
		}
		return false;
	}



	bool type_is(const Type & type, const Value & value, Heap & heap) {
		return type_is(type.code.data(), value, heap);
	}



	Value type_cast(const std::uint8_t * code, const Value & value, Heap & heap) {
		try {
			switch (*code) {
				case type_code::ANY: return value;
				case type_code::NVLL: return value::null;
				case type_code::BOOL: return value::boolean(cast::to_bool(value));
				case type_code::CHAR: return value::character(cast::to_char(value));
				case type_code::INT: return value::integer(cast::to_int(value));
				case type_code::FLOAT: return value::floating(cast::to_float(value, heap));
				case type_code::STRING: return value::string(heap.alloc(cast::to_string(value, heap)));
				case type_code::ARRAY: {
					if(is_array(value)) {
						auto & arr = heap.read<Array>(value.u);
						Array result;
						for(const auto & elem : arr) {
							result.push_back(type_cast(std::next(code), elem, heap));
						}
						return value::array(heap.alloc(std::move(result)));
					}
				}
			}
			return value::null;
		}
		catch(...) {
			return value::null;
		} 
	}



	Value type_cast(const Type & type, const Value & value, Heap & heap) {
		return type_cast(type.code.data(), value, heap);
	}
}