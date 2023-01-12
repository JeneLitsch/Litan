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
		std::uint64_t clone(std::uint64_t id) {
			auto copy = this->read<Obj>(id).clone();
			return this->alloc<Obj>(std::move(copy));
		}


		void collect_garbage(const Stack & stack, const std::vector<Value> & globals);


		void reset();


		std::uint64_t capacity() const;
		std::uint64_t utilized() const;

	private:

		void mark(const std::vector<Value> & values);
		void mark(const std::deque<Value> & values);
		void mark(const Value & value);
		void mark_array(const Value & value);
		void mark_fxptr(const Value & value);
		void mark_struct(const Value & value);
		void mark_deque(const Value & value);
		void mark_map(const Value & value);
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