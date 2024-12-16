#include "array.hxx"
#include "ltnvm/objects/container/Array.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/run_function.hxx"

namespace ltn::vm::stdlib {
	Value array_size::func(Context *, const Value * args) {
		return value::integer(req_array(args + 0)->size());
	}



	Value array_is_empty::func(Context *, const Value * args) {
		return value::boolean(req_array(args + 0)->empty());
	}



	Value array_push::func(Context *, const Value * args) {
		req_array(args + 0)->push_back(args[1]);
		return value::null;
	}



	Value array_pop::func(Context *, const Value * args) {
		Array * array = req_array(args + 0);
		return array->pop_back();
	}



	Value array_front::func(Context *, const Value * args) {
		return req_array(args + 0)->front();
	}



	Value array_back::func(Context *, const Value * args) {
		return req_array(args + 0)->back();
	}



	Value array_peek::func(Context * native_api, const Value * args) {
		return array_back::func(native_api, args);
	}



	Value array_at::func(Context *, const Value * args) {
		Array * array = req_array(args + 0);
		std::int64_t index = req_int(args + 1);
		return array->at(index);
	}



	Value array_insert::func(Context *, const Value * args) {
		Array * array = req_array(args + 0);
		std::int64_t index = req_int(args + 1);
		Value value = args[2];

		array->insert(index, value);
		return value::null;
	}



	Value array_erase::func(Context *, const Value * args) {
		Array * array = req_array(args + 0);
		std::int64_t index = req_int(args + 1);
		return array->erase(index);
	}




	Value array_values::func(Context * context, const Value * args) {
		Array * array = req_array(args + 0);
		VMCore & core = *static_cast<VMCore*>(context->core);
		return value::array(core.heap.alloc<Array>(clone(*array)));
	}



	Value array_filter::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		Array * orig_array = req_array(args + 0);
		Array * dest_array = core.heap.make<Array>();
		for (const Value & elem : *orig_array) {
			const bool result = convert::to_bool(run_function(core, args[1], elem), core);
			if (result) {
				dest_array->push_back(elem);
			}
		}
		return value::array(dest_array);
	}



	Value array_transform::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		Array * orig_array = req_array(args + 0);
		Array * dest_array = core.heap.make<Array>();
		for (const Value & elem : *orig_array) {
			dest_array->push_back(run_function(core, args[1], elem));
		}
		return value::array(dest_array);
	}



	Value array_reduce::func(Context * context, const Value * args) {
		Array * array = req_array(args + 0);
		if(std::empty(*array)) {
			return value::null;
		}

		Value sum = array->unsafe_front();
		VMCore & core = *static_cast<VMCore*>(context->core);
		for (std::int64_t i = 1; i < std::ssize(*array); i++) {
			sum = run_function(core, args[1], sum, array->unsafe_at(i));
		}
		return sum;
	}



	Value array_any::func(Context * context, const Value * args) {
		Array * array = req_array(args + 0);
		VMCore & core = *static_cast<VMCore*>(context->core);
		for (const Value & elem : *array) {
			const Value result = run_function(core, args[1], elem);
			if (convert::to_bool(result, core)) {
				return value::boolean(true);
			}
		}
		return value::boolean(false);
	}



	Value array_all::func(Context * context, const Value * args) {
		Array * array = req_array(args + 0);
		VMCore & core = *static_cast<VMCore*>(context->core);
		for (const Value & elem : *array) {
			const Value result = run_function(core, args[1], elem);
			if (!convert::to_bool(result, core)) {
				return value::boolean(false);
			}
		}
		return value::boolean(true);
	}



	Value array_has::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		Array * array = req_array(args + 0);
		const Value result = args[1];
		for (const Value & elem : *array) {
			if (compare(elem, result, core) == 0) {
				return value::boolean(true);
			}
		}
		return value::boolean(false);
	}



	Value array_none::func(Context * context, const Value * args) {
		return value::boolean(!array_any::func(context, args).b);
	}



	Value array_slice::func(Context * context, const Value * args) {
		Array * array = req_array(args + 0);
		std::int64_t begin = req_int(args + 1);
		std::int64_t end = req_int(args + 2);
		VMCore & core = *static_cast<VMCore*>(context->core);
		Array * slice = core.heap.alloc(array->slice(begin, end));
		return value::array(slice);
	}



	Value array_prefix::func(Context * context, const Value * args) {
		Array * array = req_array(args + 0);
		std::int64_t size = req_int(args + 1);
		VMCore & core = *static_cast<VMCore*>(context->core);
		Array * slice = core.heap.alloc(array->slice(0, size));
		return value::array(slice);
	}



	Value array_suffix::func(Context * context, const Value * args) {
		Array * array = req_array(args + 0);
		std::int64_t result_size = req_int(args + 1);
		std::int64_t array_size = std::ssize(*array);
		VMCore & core = *static_cast<VMCore*>(context->core);
		Array * slice = core.heap.alloc(array->slice(array_size - result_size, array_size));
		return value::array(slice);
	}



	Value array_reversed::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		Array * array = req_array(args + 0);
		Array * reversed = core.heap.alloc(array->reversed());
		return value::array(reversed);
	}
}