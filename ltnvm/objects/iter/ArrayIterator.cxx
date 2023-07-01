#include "ArrayIterator.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	ArrayIterator::ArrayIterator(Value ref) 
		: ref{ref}
		, index{0} {}
	


	Value ArrayIterator::next(Heap & heap) {
		const auto value = this->get(heap);
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value ArrayIterator::get(Heap & heap) {
		auto & arr = heap.read<Array>(this->ref);
		if(this->index < std::ssize(arr.data) && this->index >= 0) {
			return arr.data[static_cast<std::uint64_t>(this->index)];
		}
		else {
			return value::iterator_stop;
		}
	}



	void ArrayIterator::mark() {
		do_mark(this->ref);
	}



	void ArrayIterator::move(Heap &, std::int64_t amount) {
		this->index += amount;
	}



	std::uint64_t ArrayIterator::size(Heap & heap) const {
		auto & arr = heap.read<Array>(this->ref);
		return static_cast<std::uint64_t>(std::size(arr.data));
	}
}