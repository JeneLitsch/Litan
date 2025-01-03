#include "Array.hxx"
#include <algorithm>
#include "litan_vm/utils/stringify.hxx"
#include "litan_vm/stdlib/array.hxx"

namespace ltn::vm {
	namespace {
		void guard_index(const Array & array, std::int64_t i) {
			if(i < 0) {
				throw except::out_of_range();
			}
			if (i >= std::ssize(array)) {
				throw except::out_of_range();
			}
		}


		void guard_empty(const Array & array) {
			if(std::empty(array)) {
				throw except::out_of_range();
			}
		}
	}



	void Array::stringify(VMCore & core, std::ostream & oss, bool) {
		print_all(std::begin(data), std::end(data), oss, core, '[', ']');
	}



	Value Array::erase(std::int64_t i) {
		guard_index(*this, i);
		Value val = unsafe_at(i);
		unsafe_erase(std::begin(*this) + i);
		return val;
	}



	void Array::insert(std::int64_t i, Value value) {
		if(i < 0) {
			throw except::out_of_range();
		}
		if(i >= std::ssize(*this) + 1) {
			throw except::out_of_range();
		}
		unsafe_insert(std::begin(*this) + i, value);
	}



	const Value & Array::at(std::int64_t i) const {
		guard_index(*this, i);
		return unsafe_at(i);
	}



	Value & Array::at(std::int64_t i) {
		guard_index(*this, i);
		return unsafe_at(i);
	}
	


	Value Array::pop_back() {
		guard_empty(*this);
		Value val = unsafe_back();
		unsafe_pop_back();
		return val;
	}



	const Value & Array::front() const {
		guard_empty(*this);
		return unsafe_front();
	}



	const Value & Array::back() const {
		guard_empty(*this);
		return unsafe_back();
	}



	Array Array::reversed() const {
		Array copied_array = *this;
		std::reverse(std::begin(copied_array.data), std::end(copied_array.data));
		return copied_array;
	}



	Array Array::slice(std::int64_t begin, std::int64_t end) const {
		if(begin < 0) {
			throw except::out_of_range();
		}

		if(begin > std::ssize(*this)) {
			throw except::out_of_range();
		}

		if(end < 0) {
			throw except::out_of_range();
		}

		if(end > std::ssize(*this)) {
			throw except::out_of_range();
		}

		if (begin > end) {
			throw except::out_of_range();
		}

		return Array{std::vector<Value>{std::begin(*this) + begin, std::begin(*this) + end}};
	}



	Value Array::get_member(VMCore & core, std::uint64_t id) const {
		return core.types.array.get_nonstatic_member(core, id);
	}
}