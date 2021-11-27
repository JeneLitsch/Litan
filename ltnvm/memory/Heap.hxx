#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <string_view>
#include <queue>
#include "Stack.hxx"
#include "Value.hxx"
#include "Register.hxx"
#include "objects/OStream.hxx"
#include "objects/IStream.hxx"
#include "objects/FxPointer.hxx"
#include "objects/Clock.hxx"
namespace ltn::vm {
	struct Array {
		std::vector<Value> arr;
		constexpr static std::string_view typeName = "Array";
	};
	struct String {
		std::string str;
		constexpr static std::string_view typeName = "String";
	};
	struct HeapObject {
		std::variant<
				std::monostate,
				String, Array,
				IStream, OStream,
				FxPointer,
				Clock> obj;
		bool marked = false;
	};
	
	class Heap {
	public:
		Heap();
		template<class Obj>
		std::uint64_t alloc(Obj && obj) {
			if(reuse.empty()) {
				const std::uint64_t addr = this->objects.size();
				this->objects.push_back(std::move(HeapObject{obj}));
				return addr;
			}
			else {
				std::uint64_t addr = this->reuse.front();
				this->reuse.pop();
				this->objects[addr] = std::move(HeapObject{obj});
				return addr;
			}
		}

		template<class Obj>
		std::uint64_t alloc(const Obj & obj) {
			return this->alloc<Obj>(Obj{obj});
		}

		template<class Obj>
		Obj & read(std::uint64_t addr) {
			auto & object = get(addr);
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
	private:
		static auto accessViolation(std::uint64_t at, const std::string_view msg) {
			std::stringstream ss;
			ss << "Access Violation at " << at << ": " << msg;
			return std::runtime_error{ ss.str() };
		}

		void mark(const std::vector<Value> & values);
		void sweep();

		HeapObject & get(std::uint64_t addr);

		std::vector<HeapObject> objects;
		std::queue<std::uint64_t> reuse;
	};
}