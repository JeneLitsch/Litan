#include "Iterator.hxx"
#include "ArrayIterator.hxx"
#include "CombinedIterator.hxx"
#include "RangeIterator.hxx"
#include "ReversedIterator.hxx"
#include "StringIterator.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/Heap.hxx"
#include "ltnvm/utils/convert.hxx"

namespace ltn::vm {
	std::unique_ptr<Iterator> clone(const Iterator & iter) {
		return iter.clone();
	}



	namespace iterator {
		std::unique_ptr<Iterator> range(std::int64_t begin, std::int64_t end, std::int64_t step) {
			return std::make_unique<RangeIterator>(begin, end, step);
		}



		std::unique_ptr<Iterator> array(Value array) {
			return std::make_unique<ArrayIterator>(array);
		}



		std::unique_ptr<Iterator> string(Value string) {
			return std::make_unique<StringIterator>(string);
		}


		
		std::unique_ptr<Iterator> combined(std::vector<Value> refs, Heap & heap) {
			return std::make_unique<CombinedIterator>(std::move(refs), &heap);
		}



		std::unique_ptr<Iterator> reversed(Value ref) {
			return std::make_unique<ReversedIterator>(ref);
		}



		Value wrap(const Value & ref, Heap & heap) {
			if(is_iterator(ref)) return ref;
			if(is_array(ref))    return value::iterator(heap.track(iterator::array(ref)));
			if(is_tuple(ref))    return value::iterator(heap.track(iterator::array(ref)));
			if(is_string(ref))   return value::iterator(heap.track(iterator::string(ref)));
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