#include "StringIterator.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	StringIterator::StringIterator(Value ref) 
		: ref{ref}
		, index{0} {}
	


	Value StringIterator::next() {
		const auto value = this->get();
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value StringIterator::get() {
		auto * str = this->ref.as<String>(); 
		if(this->index < std::ssize(str->data) && this->index >= 0) {
			return value::character(str->data[static_cast<std::uint64_t>(this->index)]);
		}
		else {
			return value::iterator_stop;
		}
	}



	void StringIterator::mark() {
		do_mark(this->ref);
	}



	void StringIterator::move(std::int64_t amount) {
		this->index += amount;
	}



	std::uint64_t StringIterator::size() const {
		auto * str = this->ref.as<String>(); 
		return static_cast<std::uint64_t>(std::size(str->data));
	}
}