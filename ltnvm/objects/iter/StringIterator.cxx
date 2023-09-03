#include "StringIterator.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	StringIterator::StringIterator(String * string) 
		: string{string}
		, index{0}
		, version{string->get_version()} {}
	


	Value StringIterator::next() {
		const auto value = this->get();
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value StringIterator::get() {
		if(this->version != this->string->get_version()) {
			throw except::out_of_range("Invalidated map iterator");
		}
		if(this->index < std::ssize(*string) && this->index >= 0) {
			return value::character((*string)[static_cast<std::uint64_t>(this->index)]);
		}
		else {
			return value::iterator_stop;
		}
	}



	void StringIterator::mark() {
		gc::mark_obj(this->string);
	}



	void StringIterator::move(std::int64_t amount) {
		if(this->version != this->string->get_version()) {
			throw except::out_of_range("Invalidated map iterator");
		}
		this->index += amount;
	}



	std::uint64_t StringIterator::size() const {
		return static_cast<std::uint64_t>(std::size(*string));
	}



	std::unique_ptr<Iterator> StringIterator::clone() const {
		return std::make_unique<StringIterator>(*this);
	}
}