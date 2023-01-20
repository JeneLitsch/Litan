#pragma once
#include <unordered_map>
#include "memory/Heap.hxx"
#include "memory/Stack.hxx"
#include "external/Callable.hxx"

namespace ltn::vm {
	struct VmCore {
		// Runtime
		Stack stack;
		Heap heap;
		const std::uint8_t * pc;

		// Persistent
		std::span<const std::uint8_t> byte_code;

		Array static_variables;

		std::unordered_map<std::int64_t, ext::Callable> externals;
		std::unordered_map<std::string, std::uint64_t> function_table;
		std::unordered_map<std::string, std::uint64_t> static_table;
		
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
	};
}