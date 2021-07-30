#pragma once
#include <vector>
#include <stack>
#include <cstdint>
#include <variant>
namespace ltn {
	using HeapArray = std::vector<std::uint64_t>;
	using HeapStack = std::stack<std::uint64_t>;
	using HeapQueue = std::queue<std::uint64_t>;
	using HeapDeque = std::deque<std::uint64_t>;
	using HeapString = std::string;
	struct HeapObject {
		enum class Type {
			ARRAY,
			STACK,
			QUEUE,
			DEQUE,
			STRING,
		};
		
		HeapObject(Type type) : type(type) {
			switch (type) {
			case Type::ARRAY: data = HeapArray(); break;
			case Type::STACK: data = HeapStack(); break;
			case Type::QUEUE: data = HeapQueue(); break;
			case Type::DEQUE: data = HeapDeque(); break;
			case Type::STRING: data = HeapString(); break;
			}
		}

		const Type type;
		std::variant<
			HeapArray,
			HeapStack,
			HeapQueue,
			HeapString,
			HeapDeque> data;
	};
}
