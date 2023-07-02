#include "Heap.hxx"
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace ltn::vm {
	Heap::Heap() {
		this->reset();
	}


	void Heap::reset() {
		this->objects = nullptr;
		this->size = 0;
		this->next_collection = 128;
		this->growth_factor = 2;
		this->min_collection_size = 129;
	}



	std::uint64_t Heap::capacity() const {
		return 0;
	}



	std::uint64_t Heap::utilized() const {
		return 0;
	}
}

