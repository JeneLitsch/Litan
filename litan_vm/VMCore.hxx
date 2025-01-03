#pragma once
#include <unordered_map>
#include "litan_core/file/FunctionPool.hxx"
#include "litan_core/file/StringPool.hxx"
#include "litan_core/file/MemberNameTable.hxx"
#include "litan_core/file/StaticPool.hxx"
#include "litan_vm/Heap.hxx"
#include "litan_vm/VMStack.hxx"
#include "litan_vm/TypeTable.hxx"
#include "litan_vm/external/Callable.hxx"
#include "litan_vm/objects/types/NullType.hxx"
#include "litan_vm/objects/types/BoolType.hxx"
#include "litan_vm/objects/types/IntType.hxx"
#include "litan_vm/objects/types/FloatType.hxx"
#include "litan_vm/objects/types/ArrayType.hxx"
#include "litan_vm/objects/types/StringType.hxx"
#include "litan_vm/objects/types/MapType.hxx"
#include "litan_vm/objects/types/TupleType.hxx"
#include "litan_vm/objects/types/StackType.hxx"
#include "litan_vm/objects/types/QueueType.hxx"
#include "litan_vm/objects/types/StructType.hxx"
#include "litan_vm/objects/types/IStreamType.hxx"
#include "litan_vm/objects/types/OStreamType.hxx"
#include "litan_vm/objects/types/IteratorType.hxx"
#include "litan_vm/objects/types/ClockType.hxx"

namespace ltn::vm {
	struct VMCore {
		// Runtime
		VMStack stack;
		Heap heap;
		const std::uint8_t * pc;
		const std::uint8_t * code_begin;
		const std::uint8_t * code_end;

		MemberNameTable member_name_table;
		FunctionPool function_pool;
		StringPool string_pool;
		TypeTable type_table;
		StaticPool static_pool;

		struct {
			NullType null;
			BoolType boolean;
			IntType integer;
			FloatType floating;
			
			StringType string;
			ArrayType array;
			MapType map;
			TupleType tuple;
			StackType stack;
			QueueType queue;
			StructType strukt;
			IStreamType istream;
			OStreamType ostream;
			IteratorType iterator;
			ClockType clock;
		} types;
		
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