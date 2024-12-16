#include "Iterator.hxx"
#include "ContiguousIterator.hxx"
#include "CombinedIterator.hxx"
#include "RangeIterator.hxx"
#include "ReversedIterator.hxx"
#include "StringIterator.hxx"
#include "MapIterator.hxx"
#include "CoroutineIterator.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/Heap.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/convert.hxx"

namespace ltn::vm {
	void Iterator::stringify(VMCore &, std::ostream & oss, bool) {
		oss << "<iterator>";
	}



	std::unique_ptr<Iterator> clone(const Iterator & iter) {
		return iter.clone();
	}



	namespace iterator {
		Value wrap(const Value & ref, VMCore & core) {
			if(is_iterator(ref))  return ref;
			if(is_array(ref))     return value::iterator(core.heap.make<ContiguousIterator>(value::as<Array>(ref)));
			if(is_tuple(ref))     return value::iterator(core.heap.make<ContiguousIterator>(value::as<Tuple>(ref)));
			if(is_string(ref))    return value::iterator(core.heap.make<StringIterator>(value::as<String>(ref)));
			if(is_map(ref))       return value::iterator(core.heap.make<MapIterator>(value::as<Map>(ref), &core.heap));
			if(is_coroutine(ref)) return value::iterator(core.heap.make<CoroutineIterator>(value::as<Coroutine>(ref), &core));
			throw except::invalid_argument("std::iter expects an iterable object");
		}



		Value next(const Value & ref) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::next expects an iterator");
			}
			return value::as<Iterator>(ref)->next();
		}


	
		Value get(const Value & ref) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::get expects an iterator");
			}
			return value::as<Iterator>(ref)->get();
		}



		void move(const Value & ref, const Value & amount) {
			const auto step = convert::to_int(amount);
				
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::iter::move expects an iterator");
			}
			return value::as<Iterator>(ref)->move(step);
		}



		std::uint64_t size(const Value & ref) {
			if(!is_iterator(ref)) {
				throw except::invalid_argument("std::iter::size expects an iterator");
			}
			return value::as<Iterator>(ref)->size();
		}
	}
}