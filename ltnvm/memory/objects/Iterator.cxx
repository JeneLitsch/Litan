#include "Iterator.hxx"
#include "iter/ArrayCore.hxx"
#include "iter/RangeCore.hxx"
#include "iter/StringCore.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/memory/Heap.hxx"

namespace ltn::vm {
	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step) {
			return Iterator { iter::RangeCore(begin, end, step) };
		}



		Iterator array(std::uint64_t array) {
			return Iterator { iter::ArrayCore(array) };
		}



		Iterator string(std::uint64_t string) {
			return Iterator { iter::StringCore(string) };
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
				throw except::invalid_argument("std::next expects an iterator");
			}
			auto & iter = heap.read<Iterator>(ref);
			return iter.get(heap);
		}
	}
}