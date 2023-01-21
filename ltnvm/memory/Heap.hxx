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
#include "objects/Library.hxx"
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
			auto copy = ltn::vm::clone(this->read<Obj>(id));
			return this->alloc<Obj>(std::move(copy));
		}


		void collect_garbage(const Stack & stack, const Array & globals);


		void reset();


		std::uint64_t capacity() const;
		std::uint64_t utilized() const;

	private:

		void mark(const Array & values);
		void mark(const std::deque<Value> & values);
		void mark(const Value & value);
		void mark_array(const Value & value);
		void mark_fxptr(const Value & value);
		void mark_struct(const Value & value);
		void mark_deque(const Value & value);
		void mark_map(const Value & value);
		void mark_library(const Value & value);
		void mark_library_fx(const Value & value);
		void mark_library_obj(const Value & value);
		void sweep();

		template<class Obj>
		inline ObjectPool<Obj> & pool_of() {
			if constexpr(std::same_as<Obj, Library>) {
				return lib_pool;
			}
			else {
				return std::get<ObjectPool<Obj>>(this->pools);
			}
		} 

		template<class Obj>
		inline const ObjectPool<Obj> & pool_of() const {
			if constexpr(std::same_as<Obj, Library>) {
				return lib_pool;
			}
			else {
				return std::get<ObjectPool<Obj>>(this->pools);
			}
		} 

		// Must be destroyed after the other pools
		// Destruction order is reverse of declarion order
		ObjectPool<Library> lib_pool;

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
			ObjectPool<RandomEngine>,
			ObjectPool<LibraryFx>,
			ObjectPool<LibraryObj>
		> pools;

		std::queue<std::uint64_t> reuse;
		std::uint64_t gc_frequency = 10;
		std::uint64_t gc_counter = 0;
	};
}