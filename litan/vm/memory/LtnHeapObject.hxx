#pragma once
#include <vector>
#include <stack>
#include <cstdint>
#include <variant>
#include "LtnHeapTypes.hxx"
namespace ltn {
	using HeapArray = std::vector<std::uint64_t>;
	using HeapStack = std::stack<std::uint64_t>;
	using HeapQueue = std::queue<std::uint64_t>;
	using HeapDeque = std::deque<std::uint64_t>;
	using HeapString = std::string;
	struct HeapObject {

		
		HeapObject(HeapType type) : type(type) {
			switch (type) {
			case HeapType::ARRAY: data = HeapArray(); break;
			case HeapType::STACK: data = HeapStack(); break;
			case HeapType::QUEUE: data = HeapQueue(); break;
			case HeapType::DEQUE: data = HeapDeque(); break;
			case HeapType::STRING: data = HeapString(); break;
			}
		}

		const HeapType type;
		std::variant<
			HeapArray,
			HeapStack,
			HeapQueue,
			HeapString,
			HeapDeque> data;
	};
}
