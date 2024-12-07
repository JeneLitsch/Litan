#include "ContiguousIterator.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	ContiguousIterator::ContiguousIterator(Contiguous * container) 
		: container{container}
		, index{0}
		, version{container->get_version()} {}
	


	Value ContiguousIterator::next() {
		const auto value = this->get();
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value ContiguousIterator::get() {
		if(this->version != this->container->get_version()) {
			throw except::out_of_range("Invalidated map iterator");
		}
		if(this->index < std::ssize(*container) && this->index >= 0) {
			return container->unsafe_at(this->index);
		}
		else {
			return value::iterator_stop;
		}
	}



	void ContiguousIterator::mark() {
		gc::mark_obj(container);
	}



	void ContiguousIterator::move(std::int64_t amount) {
		if(this->version != this->container->get_version()) {
			throw except::out_of_range("Invalidated map iterator");
		}
		this->index += amount;
	}



	std::uint64_t ContiguousIterator::size() const {
		return static_cast<std::uint64_t>(std::size(*container));
	}



	std::unique_ptr<Iterator> ContiguousIterator::clone() const {
		return std::make_unique<ContiguousIterator>(*this);
	}
}