#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <span>
#include <string_view>
#include <queue>
#include "VMStack.hxx"
#include "Value.hxx"

#include "ltnvm/objects/Type.hxx"
#include "gc.hxx"

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
		Obj * alloc(Obj && obj) {
			return this->track<Obj>(std::make_unique<Obj>(std::move(obj)));
		}



		template<class Obj>
		Obj * make(auto && ... args) {
			return this->track<Obj>(std::make_unique<Obj>(std::move(args)...));
		}



		template<class Obj>
		Obj * track(std::unique_ptr<Obj> obj_ptr) {
			obj_ptr->next_object = std::move(this->objects);
			this->objects = std::move(obj_ptr);
			++this->size;
			return static_cast<Obj*>(this->objects.get());
		}


		template<class Obj>
		Value clone(Value id) {
			auto copy = ltn::vm::clone(*value::as<Obj>(id));
			return {
				.type = id.type,
				.object = this->alloc<Obj>(std::move(copy)),
			};
		}


		template<typename ... More>
		void collect_garbage(const VMStack & stack, More && ...more) {
			if(this->size >= this->next_collection && !is_gc_locked()) {
				((gc::mark(more)), ...);
				gc::mark(stack.get_values());
				const auto collected = gc::sweep(this->objects);
				this->size -= collected;

				this->next_collection = std::max(this->size * growth_factor, min_collection_size);
			}
		}


		void reset();


		std::uint64_t capacity() const;
		std::uint64_t utilized() const;

		void lock_gc() {
			gc_lock_stack += 1;
		}
		
		void unlock_gc() {
			gc_lock_stack -= 1;
		}

		bool is_gc_locked() const {
			return gc_lock_stack > 0;
		}

	private:
		std::int64_t gc_lock_stack = 0;
		std::unique_ptr<Object> objects;

		std::uint64_t size;
		std::uint64_t next_collection;
		std::uint64_t growth_factor;
		std::uint64_t min_collection_size;
	};
}