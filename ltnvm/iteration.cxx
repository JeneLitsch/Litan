#include "ltnvm/iteration.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::iteration {

	namespace {
		Value iter_array(const Value & value, Heap & heap) {
			return value::iterator(heap.alloc(iterator::array(value.u)));
		}



		Value iter_string(const Value & value, Heap & heap) {
			return value::iterator(heap.alloc(iterator::string(value.u)));
		}



		Value iter_tuple(const Value & value, Heap & heap) {
			return value::iterator(heap.alloc(iterator::array(value.u)));
		}
	}



	Value wrap(const Value & ref, Heap & heap) {
		if(is_iterator(ref)) return ref;
		if(is_array(ref))    return iter_array(ref, heap);
		if(is_tuple(ref))    return iter_tuple(ref, heap);
		if(is_string(ref))   return iter_string(ref, heap);
		throw except::invalid_argument("std::iter expects an iterable object");
	}



	namespace {
		bool is_done(Iterator::Range & iter) {
			if(iter.begin <= iter.end) {
				return iter.current >= iter.begin && iter.current < iter.end;
			}
			else {
				return iter.current <= iter.begin && iter.current > iter.end;
			}
		}
		
		
		
		bool is_done(Iterator::Array & iter, auto & arr) {
			return iter.index < std::size(arr);
		}



		bool is_done(Iterator::String & iter, auto & str) {
			return iter.index < std::size(str);
		}



		Value next_range(Iterator::Range & iter) {
			if(is_done(iter)) {
				auto prev = iter.current;
				iter.current += iter.step;
				return value::integer(prev);
			}
			else {
				return value::iterator_stop;
			}
		}



		Value next_array(Iterator::Array & iter, Heap & heap) {
			auto & arr = heap.read<Array>(iter.array);
			if(is_done(iter, arr)) {
				return arr[iter.index++];
			}
			else {
				return value::iterator_stop;
			}
		}



		Value next_string(Iterator::String & iter, Heap & heap) {
			auto & str = heap.read<String>(iter.string);
			if(is_done(iter, str)) {
				return value::character(str[iter.index++]);
			}
			else {
				return value::iterator_stop;
			}
		}
	}



	Value next(const Value & ref, Heap & heap) {
		if(!is_iterator(ref)) {
			throw except::invalid_argument("std::next expects an iterator");
		}
		auto & iter = heap.read<Iterator>(ref);
		
		switch (iter.type) {
			case Iterator::Type::RANGE: return next_range(iter.range);
			case Iterator::Type::ARRAY: return next_array(iter.array, heap);
			case Iterator::Type::STRING: return next_string(iter.string, heap);
		}
	}
}