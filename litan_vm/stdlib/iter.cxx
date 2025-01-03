#include "iter.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/utils/convert.hxx"
#include "litan_vm/inst/instructions.hxx"
#include "litan_vm/objects/iter.hxx"

namespace ltn::vm::stdlib {
	Value iter_is::func(Context * context, const Value * args) {
		return value::boolean(is_iterator(args[0]));
	}


	Value iter_cast::func(Context * context, const Value * args) {
		return iter_iter::func(context, args);
	}


	Value iter_range::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		auto begin = convert::to_int(args[0]);
		auto end = convert::to_int(args[1]);
		auto step = convert::to_int(args[2]);
		auto ptr = core.heap.make<RangeIterator>(begin, end, step);
		return value::iterator(ptr);
	}



	Value iter_next::func(Context *, const Value * args) {
		return iterator::next(args[0]);
	}



	Value iter_get::func(Context *, const Value * args) {
		return iterator::get(args[0]);
	}



	Value iter_move::func(Context *, const Value * args) {
		const auto iter = args[0];
		const auto step = args[1];
		iterator::move(iter, step);
		return value::null;
	}



	Value iter_iter::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		return iterator::wrap(args[0], core);
	}



	Value iter_is_stop::func(Context *, const Value * args) {
		return value::boolean(is_iterator_stop(args[0]));
	}



	Value iter_combined::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		auto param = args[0];
		if(!is_contiguous(param)) {
			throw except::invalid_argument();
		}
		Contiguous * arr = value::as<Contiguous>(param);
		std::vector<Iterator *> iters;
		for(auto & e : *arr) {
			iters.push_back(value::as<Iterator>(iterator::wrap(e, core)));
		}
		auto ptr =  core.heap.make<CombinedIterator>(std::move(iters), &core.heap);
		return value::iterator(ptr);
	}



	Value iter_reversed::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		auto ref = iterator::wrap(args[0], core);
		auto ptr = core.heap.make<ReversedIterator>(ref);
		return value::iterator(ptr);
	}
}