#include "instructions.hxx"
#include "ltnvm/type_check.hxx"

namespace ltn::vm::inst {
	namespace {
		Value iter_array(const Value & value, VmCore & core) {
			return value::iterator(core.heap.alloc(iterator::array(value.u)));
		}



		Value iter_tuple (Value & value, VmCore & core) {
			return value::iterator(core.heap.alloc(iterator::array(value.u)));
		}
	}



	void iter(VmCore & core) {
		auto ref = core.stack.pop();
		if(is_iterator(ref)) return core.stack.push(ref);
		if(is_array(ref))    return core.stack.push(iter_array(ref, core));
		if(is_tuple(ref))    return core.stack.push(iter_tuple(ref, core));
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



		Value next_array(Iterator::Array & iter, VmCore & core) {
			auto & arr = core.heap.read<Array>(iter.array);
			if(is_done(iter, arr)) {
				return arr[iter.index++];
			}
			else {
				return value::iterator_stop;
			}
		}
	}



	void next(VmCore & core) {
		auto ref = core.stack.pop();
		if(!is_iterator(ref)) {
			throw except::invalid_argument("std::next expects an iterator");
		}
		auto & iter = core.heap.read<Iterator>(ref);
		
		switch (iter.type) {
			case Iterator::Type::RANGE: return core.stack.push(next_range(iter.range));
			case Iterator::Type::ARRAY: return core.stack.push(next_array(iter.array, core));
		}
	}



	void done(VmCore & core) {
		auto value = core.stack.pop();
		core.stack.push(value::boolean(is_iterator_stop(value)));
	}
}