#include "Array.hxx"
#include <algorithm>
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/stdlib/array.hxx"

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



	void Array::stringify(VMCore & core, std::ostream & oss, bool nested) {
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

		if(begin > this->size()) {
			throw except::out_of_range();
		}

		if(end < 0) {
			throw except::out_of_range();
		}

		if(end > this->size()) {
			throw except::out_of_range();
		}

		if (begin > end) {
			throw except::out_of_range();
		}

		return Array{std::vector<Value>{std::begin(*this) + begin, std::begin(*this) + end}};
	}



	Value Array::get_member(std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::array_size>     (MemberCode::SIZE),
			wrap<stdlib::array_is_empty> (MemberCode::IS_EMTPY),
			wrap<stdlib::array_push>     (MemberCode::PUSH),
			wrap<stdlib::array_pop>      (MemberCode::POP),
			wrap<stdlib::array_front>    (MemberCode::FRONT),
			wrap<stdlib::array_back>     (MemberCode::BACK),
			wrap<stdlib::array_peek>     (MemberCode::PEEK),
			wrap<stdlib::array_at>       (MemberCode::AT),
			wrap<stdlib::array_insert>   (MemberCode::INSERT),
			wrap<stdlib::array_erase>    (MemberCode::ERASE),
			wrap<stdlib::array_values>   (MemberCode::VALUES),
			wrap<stdlib::array_filter>   (MemberCode::FILTER),
			wrap<stdlib::array_transform>(MemberCode::TRANSFORM),
			wrap<stdlib::array_reduce>   (MemberCode::REDUCE),
			wrap<stdlib::array_any>      (MemberCode::ANY),
			wrap<stdlib::array_all>      (MemberCode::ALL),
			wrap<stdlib::array_none>     (MemberCode::NONE),
			wrap<stdlib::array_has>      (MemberCode::HAS),
			wrap<stdlib::array_slice>    (MemberCode::SLICE),
			wrap<stdlib::array_prefix>   (MemberCode::PREFIX),
			wrap<stdlib::array_suffix>   (MemberCode::SUFFIX),
			wrap<stdlib::array_reversed> (MemberCode::REVERSED),
		};

		return search_native_function_table(native_function_table, id);
	}
}