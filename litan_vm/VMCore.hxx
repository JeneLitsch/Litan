#pragma once
#include <unordered_map>
#include "litan_vm/Heap.hxx"
#include "litan_vm/VMStack.hxx"
#include "litan_vm/TypeTable.hxx"
#include "litan_core/file/FunctionPool.hxx"
#include "litan_core/file/StringPool.hxx"
#include "external/Callable.hxx"

namespace ltn::vm {
	struct VMCore {
		// Runtime
		VMStack stack;
		Heap heap;
		const std::uint8_t * pc;
		const std::uint8_t * code_begin;
		const std::uint8_t * code_end;

		std::unordered_map<std::uint64_t, std::string> member_name_table;

		FunctionPool function_pool;
		StringPool string_pool;
		TypeTable type_table;
		
		inline std::uint8_t fetch_byte() {
			return *this->pc++;
		}
	

		inline std::uint64_t fetch_uint() {
			std::uint64_t value = 0;
			for(auto i = 0; i < 8; i++) {
				value <<= 8;
				value |= static_cast<std::uint64_t>(*this->pc++);
			}
			return value;
		}

			
		inline const std::uint8_t * fetch_str() {
			return this->pc;
		}



		std::uint64_t next_id = 0;
		std::uint64_t fetch_id() {
			return next_id++;
		}
	};
}