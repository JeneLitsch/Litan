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
#include "ltnvm/objects/iter.hxx"
#include "ltnvm/objects/io.hxx"
#include "ltnvm/objects/container.hxx"
#include "ltnvm/objects/FxPointer.hxx"
#include "ltnvm/objects/Clock.hxx"
#include "ltnvm/objects/RandomEngine.hxx"
#include "ltnvm/objects/Type.hxx"
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
		Obj * alloc(Obj && obj) {
			return this->track<Obj>(std::make_unique<Obj>(std::move(obj)));
		}



		template<class Obj>
		Obj * track(std::unique_ptr<Obj> obj_ptr) {
			obj_ptr->next_object = std::move(this->objects);
			this->objects = std::move(obj_ptr);
			return static_cast<Obj*>(this->objects.get());
		}



		template<class Obj>
		Obj & read(Value value) {
			return *static_cast<Obj *>(value.object);
		}


		template<class Obj>
		Value clone(Value id) {
			auto copy = ltn::vm::clone(this->read<Obj>(id));
			return Value{ this->alloc<Obj>(std::move(copy)), id.type };
		}


		template<typename ... More>
		void collect_garbage(const Stack & stack, More && ...more) {
			if(gc_counter >= gc_frequency) {
				((this->mark(more)), ...);
				mark(stack.get_values());
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


		void mark(const std::vector<Value> & values);
		void mark(const std::deque<Value> & values);
		void mark(const Value & value);
	
	private:
		std::unique_ptr<Object> objects;

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

		std::uint64_t size = 0;
		std::uint64_t gc_frequency = 10;
		std::uint64_t gc_counter = 0;
	};



	void do_mark(const std::vector<Value> & values);
	void do_mark(const std::deque<Value> & values);
	void do_mark(const Value & value);
}