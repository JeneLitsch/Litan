#include "ArrayCore.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/type_check.hxx"

namespace ltn::vm::iter {
	ArrayCore::ArrayCore(std::uint64_t ref) 
		: ref{ref}
		, index{0} {}
	


	Value ArrayCore::next(Heap & heap) {
		const auto value = this->get(heap);
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value ArrayCore::get(Heap & heap) {
		auto & arr = heap.read<Array>(this->ref);
		if(this->index < std::ssize(arr) && this->index >= 0) {
			return arr[this->index];
		}
		else {
			return value::iterator_stop;
		}
	}



	void ArrayCore::mark(Heap & heap) {
		heap.mark(value::array(this->ref));
	}



	void ArrayCore::move(Heap &, std::int64_t amount) {
		this->index += amount;
	}
}