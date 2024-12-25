#include "ReversedIterator.hxx"
#include "litan_vm/utils/type_check.hxx"
#include "litan_vm/Heap.hxx"

namespace ltn::vm {
	ReversedIterator::ReversedIterator(Value ref)
		: ref{ref} {
		const auto size = value::as<Iterator>(ref)->size();
		value::as<Iterator>(ref)->move(static_cast<std::int64_t>(size) - 1);
	}
	


	Value ReversedIterator::next() {
		const auto value = this->get();
		this->move(1);
		return value;
	}



	Value ReversedIterator::get() {
		return value::as<Iterator>(this->ref)->get();
	}


	
	void ReversedIterator::move(std::int64_t amount) {
		return value::as<Iterator>(this->ref)->move(-amount);
	}



	void ReversedIterator::mark() {
		gc::mark(this->ref);
	}



	std::uint64_t ReversedIterator::size() const {
		return value::as<Iterator>(this->ref)->size();
	}



	std::unique_ptr<Iterator> ReversedIterator::clone() const {
		return std::make_unique<ReversedIterator>(*this);
	}
}