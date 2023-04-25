#include "StringCore.hxx"
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::iter {
	StringCore::StringCore(std::uint64_t ref) 
		: ref{ref}
		, index{0} {}
	


	Value StringCore::next(Heap & heap) {
		auto & arr = heap.read<String>(this->ref);
		if(this->index < std::size(arr)) {
			return value::character(arr[this->index++]);
		}
		else {
			return value::iterator_stop;
		}
	}



	Value StringCore::get(Heap & heap) {
		auto & arr = heap.read<String>(this->ref);
		if(this->index < std::size(arr)) {
			return value::character(arr[this->index]);
		}
		else {
			return value::iterator_stop;
		}
	}



	void StringCore::mark(Heap & heap) {
		heap.mark(value::string(this->ref));
	}
}