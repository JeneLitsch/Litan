#include "array.hxx"
#include "litan_vm/objects/container/Array.hxx"
#include "litan_vm/utils/convert.hxx"
#include "litan_vm/VMCore.hxx"
#include "litan_vm/utils/function.hxx"

namespace ltn::vm::stdlib {
	Value array_new::func(Context * context, const Value *) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		return value::array(core.heap.make<Array>());
	}



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
			const std::array<Value, 1> transform_args = { elem };
			const bool result = convert::to_bool(invoke_function_immediatly(core, args[1], transform_args.data(), transform_args.size()), core);
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
			const std::array<Value, 1> transform_args = { elem };
			dest_array->push_back(invoke_function_immediatly(core, args[1], transform_args.data(), transform_args.size()));
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
			const std::array<Value, 2> transform_args = { sum, array->unsafe_at(i) };
			sum = invoke_function_immediatly(core, args[1], transform_args.data(), transform_args.size());
		}
		return sum;
	}



	Value array_any::func(Context * context, const Value * args) {
		Array * array = req_array(args + 0);
		VMCore & core = *static_cast<VMCore*>(context->core);
		for (const Value & elem : *array) {
			const std::array<Value, 1> transform_args = { elem };
			const Value result = invoke_function_immediatly(core, args[1], transform_args.data(), transform_args.size());
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
			const std::array<Value, 1> transform_args = { elem };
			const Value result = invoke_function_immediatly(core, args[1], transform_args.data(), transform_args.size());
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



	Value array_zipped::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		Array * array_l = req_array(args + 0);
		Array * array_r = req_array(args + 1);
		Array * array_result = core.heap.make<Array>();

		const std::int64_t min_size = std::min(std::ssize(*array_l), std::ssize(*array_r));

		for(std::int64_t i = 0; i < min_size; i++) {
			Tuple * pair = core.heap.make<Tuple>();
			pair->push_back(array_l->at(i));
			pair->push_back(array_r->at(i));
			array_result->push_back(value::tuple(pair));
		}

		return value::array(array_result);
	}
}