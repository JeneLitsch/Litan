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
#include "objects/Array.hxx"
#include "objects/String.hxx"
#include "objects/OStream.hxx"
#include "objects/IStream.hxx"
#include "objects/Iterator.hxx"
#include "objects/FxPointer.hxx"
#include "objects/Clock.hxx"
#include "objects/Struct.hxx"
#include "objects/Deque.hxx"
#include "objects/Map.hxx"
#include "objects/RandomEngine.hxx"
#include "ObjectPool.hxx"

namespace ltn::vm {
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
			return pool_of<Obj>().alloc(std::move(obj));
		}


		template<class Obj>
		Obj & read(std::uint64_t id) {
			return pool_of<Obj>().get(id);
		}


		template<class Obj>
		Obj & read(Value value) {
			return pool_of<Obj>().get(value.u);
		}


		template<class Obj>
		std::uint64_t clone(std::uint64_t id) {
			auto copy = ltn::vm::clone(this->read<Obj>(id));
			return this->alloc<Obj>(std::move(copy));
		}


		template<typename ... More>
		void collect_garbage(const Stack & stack, const Array & globals, More && ...more) {
			if(gc_counter >= gc_frequency) {
				((this->mark(more)), ...);
				mark(stack.get_values());
				mark(globals);
				sweep();
				gc_counter = 0;
			}
			else {
				++gc_counter;
			}
		}


		void reset();


		std::uint64_t capacity() const;
		std::uint64_t utilized() const;

	private:

		void mark(const Array & values);
		void mark(const std::deque<Value> & values);
		void mark(const Value & value);
		void mark_array(const Value & value);
		void mark_string(const Value & value);
		void mark_istream(const Value & value);
		void mark_iterator(const Value & value);
		void mark_ostream(const Value & value);
		void mark_fxptr(const Value & value);
		void mark_struct(const Value & value);
		void mark_deque(const Value & value);
		void mark_map(const Value & value);
		void mark_clock(const Value & value);
		void mark_rng(const Value & value);
		void sweep();

		template<class Obj>
		inline ObjectPool<Obj> & pool_of() {
			return std::get<ObjectPool<Obj>>(this->pools);
		} 

		template<class Obj>
		inline const ObjectPool<Obj> & pool_of() const {
			return std::get<ObjectPool<Obj>>(this->pools);
		} 

		std::tuple<
			ObjectPool<String>,
			ObjectPool<Array>,
			ObjectPool<IStream>,
			ObjectPool<Iterator>,
			ObjectPool<OStream>,
			ObjectPool<FxPointer>,
			ObjectPool<Clock>,
			ObjectPool<Struct>,
			ObjectPool<Deque>,
			ObjectPool<Map>,
			ObjectPool<RandomEngine>
		> pools;

		std::queue<std::uint64_t> reuse;
		std::uint64_t gc_frequency = 10;
		std::uint64_t gc_counter = 0;
	};
}