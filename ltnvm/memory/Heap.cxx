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
	}



	std::uint64_t Heap::size() const {
		return 
			+ pool_of<String>().size()
			+ pool_of<Array>().size()
			+ pool_of<IStream>().size()
			+ pool_of<OStream>().size()
			+ pool_of<FxPointer>().size()
			+ pool_of<Clock>().size()
			+ pool_of<Struct>().size()
			+ pool_of<Deque>().size()
			+ pool_of<Map>().size()
			+ pool_of<RandomEngine>().size();
	}
}

