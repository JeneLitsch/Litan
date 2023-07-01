#include "CombinedIterator.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/utils/type_check.hxx"
#include <limits>

namespace ltn::vm {
	CombinedIterator::CombinedIterator(std::vector<Value> iters) 
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



	void CombinedIterator::mark() {
		for(auto & ref : this->iters) {
			do_mark(ref);
			auto & iter = *ref.as<Iterator>();
			iter.mark();
		}
	}



	void CombinedIterator::move(Heap & heap, std::int64_t amount) {
		for(auto & ref : this->iters) {
			auto & iter = heap.read<Iterator>(ref);
			iter.move(heap, amount);
		}
	}



	std::uint64_t CombinedIterator::size(Heap & heap) const {
		if(std::empty(this->iters)) return 0;
		std::uint64_t size = std::numeric_limits<std::uint64_t>::max();
		for(const auto & iter_ref : this->iters) {
			const auto & iter = heap.read<Iterator>(iter_ref); 
			size = std::min(size, iter.size(heap));
		}
		return size;
	}
}