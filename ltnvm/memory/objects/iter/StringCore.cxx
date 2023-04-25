#include "StringCore.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/type_check.hxx"

namespace ltn::vm::iter {
	StringCore::StringCore(std::uint64_t ref) 
		: ref{ref}
		, index{0} {}
	


	Value StringCore::next(Heap & heap) {
		const auto value = this->get(heap);
		this->index += !is_iterator_stop(value);
		return value;
	}



	Value StringCore::get(Heap & heap) {
		auto & arr = heap.read<String>(this->ref);
		if(this->index < std::ssize(arr) && this->index >= 0) {
			return value::character(arr[this->index]);
		}
		else {
			return value::iterator_stop;
		}
	}



	void StringCore::mark(Heap & heap) {
		heap.mark(value::string(this->ref));
	}



	void StringCore::move(Heap &, std::int64_t amount) {
		this->index += amount;
	}
}