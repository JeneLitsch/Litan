#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/cast.hxx"
#include "ltnvm/convert.hxx"
#include "ltn/type_code.hxx"
#include <sstream>

namespace ltn::vm::inst {
	namespace {
		Value smart_copy(const std::uint8_t * type, const Value & value, VmCore & core);



		Value smart_copy_array(const std::uint8_t * subtype, const Value & value, VmCore & core) {
			if(is_array(value)) {
				const auto & old_array = core.heap.read<Array>(value.u);
				Array new_array;
				for(const auto & elem : old_array) {
					new_array.push_back(smart_copy(subtype, elem, core));
				}
				return value::array(core.heap.alloc<Array>(std::move(new_array)));		
			}

			if(is_string(value)) {
				const auto & old_string = core.heap.read<String>(value.u);
				Array new_array;
				for(const auto c : old_string) {
					new_array.push_back(smart_copy(subtype, value::character(c), core));
				}
				return value::array(core.heap.alloc<Array>(std::move(new_array)));		
			}		

			throw Exception{
				.type = Exception::Type::INVALID_ARGUMENT,
				.msg = "Value not castable to array"
			};
		}



		Value smart_copy_string(const Value & value, VmCore & core) {
			if(is_string(value)) {
				auto new_string = cast::to_string(value, core.heap);
				return value::string(core.heap.alloc<String>(std::move(new_string)));
			}

			if(is_array(value)) {
				std::string new_string;
				const auto old_array = core.heap.read<Array>(value.u);

				for(const auto & elem : old_array) {
					new_string.push_back(cast::to_char(elem));
				}

				return value::string(core.heap.alloc<String>(std::move(new_string)));
			}
			
			throw Exception {
				.type = Exception::Type::INVALID_ARGUMENT,
				.msg = "Value not castable to string"
			};
		}



		Value smart_copy(const std::uint8_t * type, const Value & value, VmCore & core) {
			switch (*type) {
			case type_code::BOOL:    return cast::to_bool(value);
			case type_code::CHAR:    return cast::to_char(value);
			case type_code::INT:     return cast::to_int(value);
			case type_code::FLOAT:   return cast::to_float(value, core.heap);
			case type_code::STRING:  return smart_copy_string(value, core);
			case type_code::ARRAY:   return smart_copy_array(type+1, value, core);
			}
			throw Exception{
				.type = Exception::Type::GENERIC_ERROR,
				.msg = "Invalid type cast"
			};
		}



		bool is_of_type(const std::uint8_t * type, const Value & value, VmCore & core) {
			switch (*type) {
			case type_code::BOOL:    return is_bool(value);
			case type_code::CHAR:    return is_char(value);
			case type_code::INT:     return is_int(value);
			case type_code::FLOAT:   return is_float(value);
			case type_code::STRING:  return is_string(value);
			case type_code::ARRAY: {
				if(is_array(value)) {
					auto & arr = core.heap.read<Array>(value.u);
					return std::all_of(std::begin(arr), std::end(arr), [&] (const auto & elem) {
						return is_of_type(type + 1, elem, core);
					});
				}
			} break;
			}
			return false;
		}



		Value conversion(const std::uint8_t * type, const Value & value, VmCore & core) {
			switch (*type) {
			case type_code::BOOL:    return convert::to_bool(value);
			case type_code::CHAR:    return convert::to_char(value);
			case type_code::INT:     return convert::to_int(value);
			case type_code::FLOAT:   return convert::to_float(value);
			}
			if(is_of_type(type, value, core)) {
				return value;
			}
			else throw Exception{
				.type = Exception::Type::GENERIC_ERROR,
				.msg = "Invalid type conversion"
			};
		}



		bool is_castable(const std::uint8_t * type, const Value & value, VmCore & core);



		bool is_castable_array(const std::uint8_t * type, const Value & value, VmCore & core) {
			if(is_array(value)) {
				auto & arr = core.heap.read<Array>(value.u);
				for(const auto & elem : arr) {
					if(!is_castable(type, elem, core)) return false;
				}
				return true;
			}
			return false;
		}



		bool is_castable(const std::uint8_t * type, const Value & value, VmCore & core) {
			switch (*type) {
			case type_code::BOOL:    return is_bool(value);
			case type_code::CHAR:    return is_char(value);
			case type_code::INT:     return is_int(value);
			case type_code::FLOAT:   return is_float(value);
			case type_code::STRING:  return is_string(value);
			case type_code::ARRAY:   return is_castable_array(type+1, value, core);
			}
			throw Exception{
				.type = Exception::Type::GENERIC_ERROR,
				.msg = "Invalid type cast"
			};
		}




		Value smart_cast(const std::uint8_t * type, const Value & value, VmCore & core) {
			return is_castable(type, value, core) ? value : value::null;
		}



		void resume_after_0_terminator(VmCore & core) {
			while (*core.pc++);
		}
	}



	void cast(VmCore & core) {
		const auto value = core.stack.pop();
		const std::uint8_t * type = core.pc;
		core.stack.push(smart_copy(type, value, core));
		resume_after_0_terminator(core);
	}



	void safe_cast(VmCore & core) {
		const auto value = core.stack.pop();
		const std::uint8_t * type = core.pc;
		core.stack.push(smart_cast(type, value, core));
		resume_after_0_terminator(core);
	}



	void copy(VmCore & core) {
		const auto value = core.stack.pop();
		const std::uint8_t * type = core.pc;
		core.stack.push(smart_copy(type, value, core));
		resume_after_0_terminator(core);
	}



	void safe_copy(VmCore & core) {
		const auto value = core.stack.pop();
		const std::uint8_t * type = core.pc;
		try {
			core.stack.push(smart_copy(type, value, core));
		}
		catch(const Exception & exception) {
			core.stack.push(value::null);
		}
		resume_after_0_terminator(core);
	}



	void cast_char(VmCore & core) {
		const auto value = core.stack.pop();
		const auto c = cast::to_char(value);
		core.stack.push(value::character(c));
	}



	void cast_int(VmCore & core) {
		const auto value = core.stack.pop();
		const auto i = cast::to_int(value);
		core.stack.push(value::integer(i));
	}



	void cast_float(VmCore & core) {
		const auto value = core.stack.pop();
		const auto f = cast::to_float(value, core.heap);
		core.stack.push(value::floating(f));
	}



	void cast_string(VmCore & core) {
		const auto value = core.stack.pop();
		if(is_string(value)) {
			core.stack.push(value);
		}
		else {
			auto str = cast::to_string(value, core.heap);
			const auto ref = core.heap.alloc<String>(std::move(str));
			core.stack.push(Value{ref, Value::Type::STRING});
		}
	}



	void cast_bool(VmCore & core) {
		const auto value = core.stack.pop();
		const auto b = cast::to_bool(value);
		core.stack.push(Value(b));
	}



	void conversion(VmCore & core) {
		const auto value = core.stack.pop();
		const std::uint8_t * type = core.pc;
		core.stack.push(conversion(type, value, core));
		resume_after_0_terminator(core);
	}
}