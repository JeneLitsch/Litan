#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/cast.hxx"
#include "ltn/type_code.hxx"
#include <sstream>

namespace ltn::vm::inst {
	namespace {
		Value smart_cast(const std::uint8_t * type, const Value & value, VmCore & core);



		Value smart_cast_array(const std::uint8_t * subtype, const Value & value, VmCore & core) {
			if(is_array(value)) {
				const auto & old_array = core.heap.read<Array>(value.u);
				Array new_array;
				for(const auto & elem : old_array.get()) {
					new_array.arr.push_back(smart_cast(subtype, elem, core));
				}
				const auto addr = core.heap.alloc(std::move(new_array));
				return value::array(addr);
			}


			if(is_string(value)) {
				const auto & old_string = core.heap.read<String>(value.u);
				Array new_array;
				for(const auto c : old_string.get()) {
					new_array.arr.push_back(smart_cast(subtype, value::character(c), core));
				}
				const auto addr = core.heap.alloc(std::move(new_array));
				return value::array(addr);		
			}
						

			throw Exception{
				.type = Exception::Type::INVALID_ARGUMENT,
				.msg = "Value not castable to array"
			};
		}



		Value smart_cast_string(const Value & value, VmCore & core) {
			const auto new_string = cast::to_string(value, core.heap);
			const auto addr = core.heap.alloc(String{new_string});
			return value::string(addr);
		}



		Value smart_cast(const std::uint8_t * type, const Value & value, VmCore & core) {
			// std::cout << *type << "\n";
			switch (*type) {
			case type_code::BOOL:    return cast::to_bool(value);
			case type_code::CHAR:    return cast::to_char(value);
			case type_code::INT:     return cast::to_int(value, core.heap);
			case type_code::FLOAT:   return cast::to_float(value, core.heap);
			case type_code::STRING:  return smart_cast_string(value, core);
			case type_code::ARRAY:   return smart_cast_array(type+1, value, core);
			}
			throw Exception{
				.type = Exception::Type::GENERIC_ERROR,
				.msg = "Invalid type cast"
			};
		}
	}



	void cast(VmCore & core) {
		const auto value = core.reg.pop();
		const std::uint8_t * type = &core.byte_code[core.pc];
		core.reg.push(smart_cast(type, value, core));
		while (core.byte_code[core.pc++]); // Resume after \0 terminator
	}



	void cast_char(VmCore & core) {
		const auto value = core.reg.pop();
		const auto c = cast::to_char(value);
		core.reg.push(value::character(c));
	}



	void cast_int(VmCore & core) {
		const auto value = core.reg.pop();
		const auto i = cast::to_int(value, core.heap);
		core.reg.push(value::integer(i));
	}



	void cast_float(VmCore & core) {
		const auto value = core.reg.pop();
		const auto f = cast::to_float(value, core.heap);
		core.reg.push(value::floating(f));
	}



	void cast_string(VmCore & core) {
		const auto value = core.reg.pop();
		if(is_string(value)) {
			core.reg.push(value);
		}
		else {
			const auto str = cast::to_string(value, core.heap);
			const auto ref = core.heap.alloc<String>(String{str});
			core.reg.push(Value{ref, Value::Type::STRING});
		}
	}



	void cast_bool(VmCore & core) {
		const auto value = core.reg.pop();
		const auto b = cast::to_bool(value);
		core.reg.push(Value(b));
	}



	void cast_array(VmCore & core) {
		const auto ref = core.reg.pop();
		
		if(is_array(ref)) {
			core.reg.push(ref);
			return;
		}

		if(is_range(ref)) {
			const auto & range = core.heap.read<Range>(ref.u);
			const auto arrRef = value::array(range.array);
			core.reg.push(arrRef);
			return;
		}

		auto && array = cast::to_array(ref);
		const auto ptr = core.heap.alloc<Array>({std::move(array)});
		const auto arrRef = value::array(ptr); 
		core.reg.push(arrRef);
	}
}