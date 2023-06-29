#include "Heap.hxx"
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace ltn::vm {
	Heap::Heap() {}


	void Heap::reset() {
		this->objects = nullptr;
	}



	std::uint64_t Heap::capacity() const {
		return 0;
	}



	std::uint64_t Heap::utilized() const {
		return 0;
	}
}

