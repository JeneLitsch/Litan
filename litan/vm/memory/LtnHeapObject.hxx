#pragma once
#include <vector>
#include <stack>
#include <cstdint>
#include <variant>
namespace ltn {
	using HeapArray = std::vector<std::uint64_t>;
	using HeapStack = std::stack<std::uint64_t>;
	using HeapString = std::string;
	struct HeapObject {
		enum class Type {
			ARRAY,
			STACK,
			STRING,
		};
		
		HeapObject(Type type) : type(type) {
			switch (type) {
			case Type::ARRAY: data = HeapArray(); break;
			case Type::STACK: data = HeapStack(); break;
			case Type::STRING: data = HeapString(); break;
			}
			this->refCount = 1;
		}

		const Type type;
		unsigned refCount;
		std::variant<HeapArray, HeapStack, HeapString> data;
	};
}
