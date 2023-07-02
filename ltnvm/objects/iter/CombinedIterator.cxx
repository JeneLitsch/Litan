#include "CombinedIterator.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/utils/type_check.hxx"
#include <limits>

namespace ltn::vm {
	CombinedIterator::CombinedIterator(std::vector<Iterator *> iters, Heap * heap) 
		: iters{std::move(iters)}
		, heap{heap} {}
	


	Value CombinedIterator::next() {
		const auto value = this->get();
		if(!is_iterator_stop(value)) {
			this->move(1);
		}
		return value;
	}



	Value CombinedIterator::get() {
		Array tuple;
		for(auto * iter : this->iters) {
			auto elem = iter->get();
			tuple.push_back(elem);
			if(is_iterator_stop(elem)) {
				return value::iterator_stop;
			}
		}
		return value::tuple(this->heap->alloc(std::move(tuple)));
	}



	void CombinedIterator::mark() {
		for(auto * iter : this->iters) {
			gc::mark_obj(iter);
		}
	}



	void CombinedIterator::move(std::int64_t amount) {
		for(auto * iter : this->iters) {
			iter->move(amount);
		}
	}



	std::uint64_t CombinedIterator::size() const {
		if(std::empty(this->iters)) return 0;
		std::uint64_t size = std::numeric_limits<std::uint64_t>::max();
		for(auto * iter : this->iters) {
			size = std::min(size, iter->size());
		}
		return size;
	}


	
	std::unique_ptr<Iterator> CombinedIterator::clone() const {
		return std::make_unique<CombinedIterator>(*this);
	}
}