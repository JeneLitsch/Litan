#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		void unpack_tuple(int size, const Value & ref, VMStack & stack, Heap & heap) {
			auto & tuple = heap.read<Tuple>(ref);
			if(std::ssize(tuple) < size) {
				throw Exception{Exception::Type::OUT_OF_RANGE, "Cannot unpack tuple"};
			}
			for(int i = size - 1; i >= 0; --i) {
				stack.push(tuple[static_cast<std::size_t>(i)]);
			}
		}
	}

	void unpack(VMCore & core) {
		auto size = core.fetch_byte();
		auto ref = core.stack.pop();
		if(is_tuple(ref)) {
			return unpack_tuple(size, ref, core.stack, core.heap);
		} 
		throw Exception{Exception::Type::INVALID_ARGUMENT, "Not a tuple"};
	}
}