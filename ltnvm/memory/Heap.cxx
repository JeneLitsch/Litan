#include "Heap.hxx"
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace ltn::vm {
	Heap::Heap() {}


	void Heap::reset() {
		pool_of<String>().clear();
		pool_of<Array>().clear();
		pool_of<IStream>().clear();
		pool_of<OStream>().clear();
		pool_of<FxPointer>().clear();
		pool_of<Clock>().clear();
		pool_of<Struct>().clear();
		pool_of<Deque>().clear();
		pool_of<Map>().clear();
		pool_of<RandomEngine>().clear();
		pool_of<Library>().clear();
		pool_of<LibraryFx>().clear();
		pool_of<LibraryObj>().clear();
	}



	std::uint64_t Heap::capacity() const {
		return 
			+ pool_of<String>().capacity()
			+ pool_of<Array>().capacity()
			+ pool_of<IStream>().capacity()
			+ pool_of<OStream>().capacity()
			+ pool_of<FxPointer>().capacity()
			+ pool_of<Clock>().capacity()
			+ pool_of<Struct>().capacity()
			+ pool_of<Deque>().capacity()
			+ pool_of<Map>().capacity()
			+ pool_of<RandomEngine>().capacity()
			+ pool_of<Library>().capacity()
			+ pool_of<LibraryFx>().capacity()
			+ pool_of<LibraryObj>().capacity();
	}



	std::uint64_t Heap::utilized() const {
		return 
			+ pool_of<String>().utilized()
			+ pool_of<Array>().utilized()
			+ pool_of<IStream>().utilized()
			+ pool_of<OStream>().utilized()
			+ pool_of<FxPointer>().utilized()
			+ pool_of<Clock>().utilized()
			+ pool_of<Struct>().utilized()
			+ pool_of<Deque>().utilized()
			+ pool_of<Map>().utilized()
			+ pool_of<RandomEngine>().utilized()
			+ pool_of<Library>().utilized()
			+ pool_of<LibraryFx>().utilized()
			+ pool_of<LibraryObj>().utilized();
	}
}

