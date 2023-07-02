#include "StringIterator.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	StringIterator::StringIterator(String * string) 
		: string{string}
		, index{0} {}
	


	Value StringIterator::next() {
		const auto value = this->get();
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value StringIterator::get() {
		if(this->index < std::ssize(string->data) && this->index >= 0) {
			return value::character(string->data[static_cast<std::uint64_t>(this->index)]);
		}
		else {
			return value::iterator_stop;
		}
	}



	void StringIterator::mark() {
		gc::mark(value::string(this->string));
	}



	void StringIterator::move(std::int64_t amount) {
		this->index += amount;
	}



	std::uint64_t StringIterator::size() const {
		return static_cast<std::uint64_t>(std::size(string->data));
	}



	std::unique_ptr<Iterator> StringIterator::clone() const {
		return std::make_unique<StringIterator>(*this);
	}
}