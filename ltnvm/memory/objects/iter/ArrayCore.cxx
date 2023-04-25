#include "ArrayCore.hxx"
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::iter {
	ArrayCore::ArrayCore(std::uint64_t ref) 
		: ref{ref}
		, index{0} {}
	


	Value ArrayCore::next(Heap & heap) {
		auto & arr = heap.read<Array>(this->ref);
		if(this->index < std::size(arr)) {
			return arr[this->index++];
		}
		else {
			return value::iterator_stop;
		}
	}


	void ArrayCore::mark(Heap & heap) {
		heap.mark(value::array(this->ref));
	}
}