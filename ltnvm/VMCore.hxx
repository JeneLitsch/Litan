#pragma once
#include <unordered_map>
#include "ltnvm/Heap.hxx"
#include "ltnvm/VMStack.hxx"
#include "ltnvm/TypeTable.hxx"
#include "ltn/file/FunctionPool.hxx"
#include "ltn/file/StringPool.hxx"
#include "external/Callable.hxx"

namespace ltn::vm {
	struct VMCore {
		// Runtime
		VMStack stack;
		Heap heap;
		const std::uint8_t * pc;
		const std::uint8_t * code_begin;
		const std::uint8_t * code_end;

		std::unordered_map<std::int64_t, ext::Callable> fx_table_ltn_to_cxx;
		std::unordered_map<std::string, std::uint64_t> static_table;
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