#include "Iterator.hxx"
#include "iter/ArrayIterator.hxx"
#include "iter/CombinedIterator.hxx"
#include "iter/RangeIterator.hxx"
#include "iter/ReversedIterator.hxx"
#include "iter/StringIterator.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/Heap.hxx"
#include "ltnvm/utils/convert.hxx"

namespace ltn::vm {
	Iterator clone(const Iterator & iter) {
		return iter.clone();
	}



	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step) {
			return RangeIterator(begin, end, step);
		}



		Iterator array(Value array) {
			return ArrayIterator(array);
		}



		Iterator string(Value string) {
			return StringIterator(string);
		}


		
		Iterator combined(std::vector<Value> refs, Heap & heap) {
			return CombinedIterator(std::move(refs), &heap);
		}



		Iterator reversed(Value ref) {
			return ReversedIterator(ref);
		}



		Value wrap(const Value & ref, Heap & heap) {
			if(is_iterator(ref)) return ref;
			if(is_array(ref))    return value::iterator(heap.alloc(iterator::array(ref)));
			if(is_tuple(ref))    return value::iterator(heap.alloc(iterator::array(ref)));
			if(is_string(ref))   return value::iterator(heap.alloc(iterator::string(ref)));
			throw except::invalid_argument("std::iter expects an iterable object");
		}



		Value next(const Value & ref, Heap & heap) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::next expects an iterator");
			}
			auto & iter = heap.read<Iterator>(ref);
			return iter.next();
		}


	
		Value get(const Value & ref, Heap & heap) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::get expects an iterator");
			}
			auto & iter = heap.read<Iterator>(ref);
			return iter.get();
		}



		void move(const Value & ref, const Value & amount, Heap & heap) {
			const auto step = convert::to_int(amount);
				
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::iter::move expects an iterator");
			}
			auto & iter = heap.read<Iterator>(ref);
			return iter.move(step);
		}



		std::uint64_t size(const Value & ref, Heap & heap) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::iter::size expects an iterator");
			}
			auto & iter = heap.read<Iterator>(ref);
			return iter.size();
		}
	}
}