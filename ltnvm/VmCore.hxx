#pragma once
#include <unordered_map>
#include "memory/Heap.hxx"
#include "memory/Stack.hxx"
#include "memory/Register.hxx"
#include "external/External.hxx"

namespace ltn::vm {
	struct VmCore {
		// Runtime
		Stack stack;
		Register reg;
		Heap heap;
		std::uint64_t pc;

		// Persistent
		std::vector<std::uint8_t> byte_code;

		std::vector<Value> static_variables;

		std::unordered_map<std::int64_t, std::unique_ptr<ext::External>> externals;
		std::unordered_map<std::string, std::uint64_t> function_table;
		std::unordered_map<std::string, std::uint64_t> static_table;
		
		inline std::uint8_t fetch_byte() {
			return this->byte_code[this->pc++];
		}
	

		inline std::uint64_t fetch_uint() {
			std::uint64_t value = 0;
			for(auto i = 0; i < 8; i++) {
				value <<= 8;
				value |= static_cast<std::uint64_t>(this->byte_code[this->pc++]);
			}
			return value;
		}

			
		inline const std::uint8_t * fetch_str() {
			return this->byte_code.data() + this->pc;
		}
	};
}