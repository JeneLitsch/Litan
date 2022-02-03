#include "Heap.hxx"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "ltnvm/TypeCheck.hxx"

namespace ltn::vm {
	Heap::Heap() {}


	HeapObject & ltn::vm::Heap::get(std::uint64_t addr) {
		if(addr > this->objects.size()) {
			throw accessViolation(addr, "");
		}
		return this->objects[addr];
	}

	void Heap::collectGarbage(const Stack & stack, const Register & reg) {
		mark(stack.getContainer());
		mark(reg.getContainer());
		sweep();
	}

	void Heap::mark(const std::vector<Value> & values) {
		for(const auto & value : values) {
			this->mark(value);
		}
	}

	void Heap::mark(const Struct::Members & members) {
		for(const auto & [key, value] : members) {
			this->mark(value);
		}
	}


	void Heap::mark(const Value & value) {
		if(isArr(value)) {
			auto & obj = this->get(value.u);
			if(!obj.marked) {
				auto & arr = this->read<Array>(value.u);
				obj.marked = true;
				this->mark(arr.arr);
			}
		}
		
		else if(isFxPtr(value)) {
			auto & obj = get(value.u);
			if(!obj.marked) {
				auto & fx = this->read<FxPointer>(value.u);
				obj.marked = true;
				this->mark(fx.captured);
			}
		}

		else if(isStruct(value)) {
			auto & obj = get(value.u);
			if(!obj.marked) {
				auto & fx = this->read<Struct>(value.u);
				obj.marked = true;
				this->mark(fx.members);
			}
		}
		
		else if(
			isStr(value) ||
			isOStream(value) ||
			isIStream(value) ||
			isClock(value)) {
			auto & obj = this->get(value.u);
			obj.marked = true;
		}
	}

	void ltn::vm::Heap::sweep() {
		std::uint64_t idx = 0;
		for(auto & obj : this->objects) {
			if(obj.marked) {
				obj.marked = false;
			}
			else if(!std::get_if<std::monostate>(&obj.obj)) {
				obj.obj = std::monostate();
				this->reuse.push(idx);
				// std::cout << "Delete " << idx << "\n";
			}
			idx++;
		}
	}

	void Heap::reset() {
		this->objects.clear();
		this->reuse = {};
	}

	std::size_t Heap::size() const {
		const auto begin = this->objects.begin();
		const auto end = this->objects.end();
		
		constexpr static auto pred = [] (const HeapObject & obj ) {
			return !std::get_if<std::monostate>(&obj.obj);
		};
		
		const auto result = std::count_if(begin, end, pred);
		
		return static_cast<std::uint64_t>(result);
	}
}

