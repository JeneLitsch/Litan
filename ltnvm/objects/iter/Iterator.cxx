#include "Iterator.hxx"
#include "ContiguousIterator.hxx"
#include "CombinedIterator.hxx"
#include "RangeIterator.hxx"
#include "ReversedIterator.hxx"
#include "StringIterator.hxx"
#include "MapIterator.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/Heap.hxx"
#include "ltnvm/utils/convert.hxx"

namespace ltn::vm {
	std::unique_ptr<Iterator> clone(const Iterator & iter) {
		return iter.clone();
	}



	namespace iterator {
		Value wrap(const Value & ref, Heap & heap) {
			if(is_iterator(ref)) return ref;
			if(is_array(ref))    return value::iterator(heap.make<ContiguousIterator>(ref.as<Array>()));
			if(is_tuple(ref))    return value::iterator(heap.make<ContiguousIterator>(ref.as<Tuple>()));
			if(is_string(ref))   return value::iterator(heap.make<StringIterator>(ref.as<String>()));
			if(is_map(ref))      return value::iterator(heap.make<MapIterator>(ref.as<Map>(), &heap));
			throw except::invalid_argument("std::iter expects an iterable object");
		}



		Value next(const Value & ref) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::next expects an iterator");
			}
			return ref.as<Iterator>()->next();
		}


	
		Value get(const Value & ref) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::get expects an iterator");
			}
			return ref.as<Iterator>()->get();
		}



		void move(const Value & ref, const Value & amount) {
			const auto step = convert::to_int(amount);
				
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::iter::move expects an iterator");
			}
			return ref.as<Iterator>()->move(step);
		}



		std::uint64_t size(const Value & ref) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::iter::size expects an iterator");
			}
			return ref.as<Iterator>()->size();
		}
	}
}