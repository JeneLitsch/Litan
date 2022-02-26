#include "Heap.hxx"
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace ltn::vm {
	Heap::Heap() {}


	HeapObject & ltn::vm::Heap::get(std::uint64_t addr) {
		if(addr > this->objects.size()) {
			throw access_violation(addr, "");
		}
		return this->objects[addr];
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

