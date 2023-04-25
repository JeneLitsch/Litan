#include "Iterator.hxx"
#include "iter/ArrayIterator.hxx"
#include "iter/RangeIterator.hxx"
#include "iter/StringIterator.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/convert.hxx"

namespace ltn::vm {
	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step) {
			return RangeIterator(begin, end, step);
		}



		Iterator array(std::uint64_t array) {
			return ArrayIterator(array);
		}



		Iterator string(std::uint64_t string) {
			return StringIterator(string);
		}


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



		Value next(const Value & ref, Heap & heap) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::next expects an iterator");
			}
			auto & iter = heap.read<Iterator>(ref);
			return iter.next(heap);
		}


	
		Value get(const Value & ref, Heap & heap) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::get expects an iterator");
			}
			auto & iter = heap.read<Iterator>(ref);
			return iter.get(heap);
		}



		void move(const Value & ref, const Value & amount, Heap & heap) {
			const auto step = convert::to_int(amount);
				
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::iter::advance expects an iterator");
			}
			auto & iter = heap.read<Iterator>(ref);
			return iter.move(heap, step);
		}
	}
}