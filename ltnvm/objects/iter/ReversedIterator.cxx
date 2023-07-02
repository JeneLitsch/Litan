#include "ReversedIterator.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/Heap.hxx"

namespace ltn::vm {
	ReversedIterator::ReversedIterator(Value ref)
		: ref{ref} {
		const auto size = this->ref.as<Iterator>()->size();
		this->ref.as<Iterator>()->move(static_cast<std::int64_t>(size) - 1);
	}
	


	Value ReversedIterator::next() {
		const auto value = this->get();
		this->move(1);
		return value;
	}



	Value ReversedIterator::get() {
		return this->ref.as<Iterator>()->get();
	}


	
	void ReversedIterator::move(std::int64_t amount) {
		return this->ref.as<Iterator>()->move(-amount);
	}



	void ReversedIterator::mark() {
		gc::mark(this->ref);
	}



	std::uint64_t ReversedIterator::size() const {
		return this->ref.as<Iterator>()->size();
	}



	std::unique_ptr<Iterator> ReversedIterator::clone() const {
		return std::make_unique<ReversedIterator>(*this);
	}
}