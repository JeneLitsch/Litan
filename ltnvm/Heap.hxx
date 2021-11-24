#pragma once
#include <string>
#include <vector>
#include <variant>
#include <queue>
#include "Value.hxx"
#include "Stack.hxx"
#include "Register.hxx"
namespace ltn::vm {
	using Array = std::vector<Value>;
	using String = std::string;
	struct HeapObject {
		std::variant<
				String, Array, std::monostate> obj;
		bool marked = false;
	};
	
	class Heap {
	public:
		Heap();
		std::uint64_t allocString();
		std::uint64_t allocArray();

		String & readString(std::uint64_t addr);
		Array & readArray(std::uint64_t addr);

		void collectGarbage(const Stack & stack, const Register & reg);
	private:
		void mark(const std::vector<Value> & values);
		void sweep();

		HeapObject & get(std::uint64_t addr);
		std::uint64_t alloc(const HeapObject & object);
		std::vector<HeapObject> objects;
		std::queue<std::uint64_t> reuse;
	};
}