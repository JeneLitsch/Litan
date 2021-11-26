#pragma once
#include <string>
#include <vector>
#include <variant>
#include <queue>
#include "Value.hxx"
#include "Stack.hxx"
#include "Register.hxx"
#include "OStream.hxx"
#include "IStream.hxx"
#include "FxPointer.hxx"
namespace ltn::vm {
	using Array = std::vector<Value>;
	using String = std::string;
	struct HeapObject {
		std::variant<
				std::monostate,
				String, Array,
				IStream, OStream,
				FxPointer> obj;
		bool marked = false;
	};
	
	class Heap {
	public:
		Heap();
		std::uint64_t allocString(const std::string & str = "");
		std::uint64_t allocArray(const Array & arr = {});
		std::uint64_t allocOStream(const OStream & out = {std::cout});
		std::uint64_t allocIStream(const IStream & out = {std::cin});
		std::uint64_t allocFxPointer(FxPointer fxPtr);

		String & readString(std::uint64_t addr);
		Array & readArray(std::uint64_t addr);
		OStream & readOStream(std::uint64_t addr);
		IStream & readIStream(std::uint64_t addr);
		FxPointer & readFxPointer(std::uint64_t addr);

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