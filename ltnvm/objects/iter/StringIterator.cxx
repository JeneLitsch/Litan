#include "StringIterator.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	StringIterator::StringIterator(Value ref) 
		: ref{ref}
		, index{0} {}
	


	Value StringIterator::next(Heap & heap) {
		const auto value = this->get(heap);
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value StringIterator::get(Heap & heap) {
		auto & arr = heap.read<String>(this->ref);
		if(this->index < std::ssize(arr.data) && this->index >= 0) {
			return value::character(arr.data[static_cast<std::uint64_t>(this->index)]);
		}
		else {
			return value::iterator_stop;
		}
	}



	void StringIterator::mark(Heap & heap) {
		heap.mark(this->ref);
	}



	void StringIterator::move(Heap &, std::int64_t amount) {
		this->index += amount;
	}



	std::uint64_t StringIterator::size(Heap & heap) const {
		auto & str = heap.read<String>(this->ref);
		return static_cast<std::uint64_t>(std::size(str.data));
	}
}