#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <queue>
#include "Stack.hxx"
#include "Value.hxx"
#include "Register.hxx"
#include "objects/OStream.hxx"
#include "objects/IStream.hxx"
#include "objects/FxPointer.hxx"
#include "objects/Clock.hxx"
namespace ltn::vm {
	using Array = std::vector<Value>;
	using String = std::string;
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
				if constexpr(std::same_as<Obj, String>) {
					throw accessViolation(addr, "not a String");
				}
				else if constexpr(std::same_as<Obj, Array>) {
					throw accessViolation(addr, "not a Array");
				}
				else if constexpr(std::same_as<Obj, FxPointer>) {
					throw accessViolation(addr, "not a FxPointer");
				}
				else if constexpr(std::same_as<Obj, Clock>) {
					throw accessViolation(addr, "not a Clock");
				}
				else throw accessViolation(addr, "Unknwo Object");
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
		std::uint64_t alloc_(const HeapObject & object);

		std::vector<HeapObject> objects;
		std::queue<std::uint64_t> reuse;
	};
}