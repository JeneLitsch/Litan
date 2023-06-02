#include "ReversedIterator.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/objects/Iterator.hxx"
#include "ltnvm/Heap.hxx"

namespace ltn::vm {
	ReversedIterator::ReversedIterator(std::int64_t ref, Heap & heap)
		: ref{ref} {
		const auto size = iterator::size(value::iterator(this->ref), heap);
		heap.read<Iterator>(ref).move(heap, size - 1);
	}
	


	Value ReversedIterator::next(Heap & heap) {
		const auto value = this->get(heap);
		this->move(heap, 1);
		return value;
	}



	Value ReversedIterator::get(Heap & heap) {
		return heap.read<Iterator>(this->ref).get(heap);
	}


	
	void ReversedIterator::move(Heap & heap, std::int64_t amount) {
		return heap.read<Iterator>(this->ref).move(heap, -amount);
	}



	void ReversedIterator::mark(Heap & heap) {
		heap.mark(value::iterator(this->ref));
	}



	std::uint64_t ReversedIterator::size(Heap & heap) const {
		return heap.read<Iterator>(this->ref).size(heap);
	}
}