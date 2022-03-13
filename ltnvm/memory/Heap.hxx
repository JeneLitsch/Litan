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
#include "objects/Map.hxx"
#include "objects/RandomEngine.hxx"
namespace ltn::vm {
	struct HeapObject {
		using Data = std::variant<
			std::monostate,
			String, Array,
			IStream, OStream,
			FxPointer,
			Clock,
			Struct, Range,
			Deque, Map,
			RandomEngine>;
 		Data obj;
		
		bool marked = false;
		
		static HeapObject clone(std::monostate) {
			return HeapObject{std::monostate{}};
		}

		static HeapObject clone(const auto & obj) {
			return HeapObject{obj.clone()};
		}
	};


	inline auto access_violation(std::uint64_t at, const std::string_view msg) {
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
				throw access_violation(addr, "");
			}
			auto & object = this->objects[addr];
			if(auto * string = std::get_if<Obj>(&object.obj)) {
				return *string;
			}
			else {
				std::stringstream ss;
				ss << "not a" << Obj::typeName;
				throw access_violation(addr, ss.str());
			}
		}


		std::uint64_t clone(std::uint64_t ptr) {
			auto & obj = this->get(ptr);
			constexpr static auto cloning = [] (const auto & data) {
				return HeapObject::clone(data);
			};
			auto newdata = std::visit(cloning, obj.obj);
			return this->alloc(newdata);
		}


		void collect_garbage(const Stack & stack, const Register & reg);


		void reset();


		std::size_t size() const;

	private:

		void mark(const std::span<const Value> values);
		void mark(const std::deque<Value> & values);
		void mark(const Value & value);
		void mark_array(const Value & value);
		void mark_fxptr(const Value & value);
		void mark_struct(const Value & value);
		void mark_range(const Value & value);
		void mark_default(const Value & value);
		void mark_deque(const Value & value);
		void mark_map(const Value & value);
		void mark_rng(const Value & value);
		void sweep();

		HeapObject & get(std::uint64_t addr);

		std::vector<HeapObject> objects;
		std::queue<std::uint64_t> reuse;
	};
}