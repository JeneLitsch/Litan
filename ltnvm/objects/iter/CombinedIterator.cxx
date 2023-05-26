#include "CombinedIterator.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	CombinedIterator::CombinedIterator(std::vector<std::uint64_t> iters) 
		: iters{std::move(iters)} {}
	


	Value CombinedIterator::next(Heap & heap) {
		const auto value = this->get(heap);
		if(!is_iterator_stop(value)) {
			this->move(heap, 1);
		}
		return value;
	}



	Value CombinedIterator::get(Heap & heap) {
		Array tuple;
		for(auto & ref : this->iters) {
			auto & iter = heap.read<Iterator>(ref);
			auto elem = iter.get(heap);
			tuple.push_back(elem);
			if(is_iterator_stop(elem)) {
				return value::iterator_stop;
			}
		}
		return value::tuple(heap.alloc(std::move(tuple)));
	}



	void CombinedIterator::mark(Heap & heap) {
		for(auto & ref : this->iters) {
			heap.mark(value::iterator(ref));
			auto & iter = heap.read<Iterator>(ref);
			iter.mark(heap);
		}
	}



	void CombinedIterator::move(Heap & heap, std::int64_t amount) {
		for(auto & ref : this->iters) {
			auto & iter = heap.read<Iterator>(ref);
			iter.move(heap, amount);
		}
	}
}