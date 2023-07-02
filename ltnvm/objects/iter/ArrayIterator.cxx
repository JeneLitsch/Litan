#include "ArrayIterator.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	ArrayIterator::ArrayIterator(Array * array) 
		: array{array}
		, index{0} {}
	


	Value ArrayIterator::next() {
		const auto value = this->get();
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value ArrayIterator::get() {
		if(this->index < std::ssize(array->data) && this->index >= 0) {
			return array->data[static_cast<std::uint64_t>(this->index)];
		}
		else {
			return value::iterator_stop;
		}
	}



	void ArrayIterator::mark() {
		gc::mark_obj(array);
	}



	void ArrayIterator::move(std::int64_t amount) {
		this->index += amount;
	}



	std::uint64_t ArrayIterator::size() const {
		return static_cast<std::uint64_t>(std::size(array->data));
	}



	std::unique_ptr<Iterator> ArrayIterator::clone() const {
		return std::make_unique<ArrayIterator>(*this);
	}
}