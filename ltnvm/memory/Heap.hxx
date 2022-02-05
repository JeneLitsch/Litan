#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <span>
#include <string_view>
#include <queue>
#include "Stack.hxx"
#include "Value.hxx"
#include "Register.hxx"
#include "objects/Array.hxx"
#include "objects/String.hxx"
#include "objects/OStream.hxx"
#include "objects/IStream.hxx"
#include "objects/FxPointer.hxx"
#include "objects/Clock.hxx"
#include "objects/Struct.hxx"
#include "objects/Range.hxx"
#include "objects/Deque.hxx"
namespace ltn::vm {
	struct HeapObject {
		std::variant<
			std::monostate,
			String, Array,
			IStream, OStream,
			FxPointer,
			Clock,
			Struct, Range,
			Deque> obj;
		
		bool marked = false;
	};

	inline auto accessViolation(std::uint64_t at, const std::string_view msg) {
		std::stringstream ss;
		ss << "Access Violation at " << at << ": " << msg;
		return std::runtime_error{ ss.str() };
	}
	
	class Heap {
	public:
		Heap();
		template<class Obj>
		std::uint64_t alloc(Obj && obj) {
			if(reuse.empty()) {
				const std::uint64_t addr = this->objects.size();
				this->objects.push_back(HeapObject{std::move(obj)});
				return addr;
			}
			else {
				std::uint64_t addr = this->reuse.front();
				this->reuse.pop();
				this->objects[addr] = HeapObject{std::move(obj)};
				return addr;
			}
		}

		template<class Obj>
		std::uint64_t alloc(const Obj & obj) {
			return this->alloc<Obj>(Obj{obj});
		}

		template<class Obj>
		Obj & read(std::uint64_t addr) {
			if(addr > this->objects.size()) {
				throw accessViolation(addr, "");
			}
			auto & object = this->objects[addr];
			if(auto * string = std::get_if<Obj>(&object.obj)) {
				return *string;
			}
			else {
				std::stringstream ss;
				ss << "not a" << Obj::typeName;
				throw accessViolation(addr, ss.str());
			}
		}

		void collectGarbage(const Stack & stack, const Register & reg);

		void reset();

		std::size_t size() const;
	private:

		void mark(const std::span<const Value> values);
		void mark(const std::deque<Value> & values);
		void mark(const Value & value);
		void markArray(const Value & value);
		void markFxPtr(const Value & value);
		void markStruct(const Value & value);
		void markRange(const Value & value);
		void markDefault(const Value & value);
		void markDeque(const Value & value);
		void sweep();

		HeapObject & get(std::uint64_t addr);

		std::vector<HeapObject> objects;
		std::queue<std::uint64_t> reuse;
	};
}