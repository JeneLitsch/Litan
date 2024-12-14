#include "tuple.hxx"
#include "ltnvm/objects/container/Tuple.hxx"
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::stdlib {
	Value tuple_size::func(Context *, const Value * args) {
		const Tuple * tuple = req_tuple(args + 0);
		return value::integer(std::size(*tuple));
	}



	Value tuple_is_empty::func(Context *, const Value * args) {
		const Tuple * tuple = req_tuple(args + 0);
		return value::boolean(std::empty(*tuple));
	}



	Value tuple_at::func(Context *, const Value * args) {
		const Tuple * tuple = req_tuple(args + 0);
		const std::int64_t index = req_int(args + 1);
		return tuple->at(index);
	}



	Value tuple_front::func(Context *, const Value * args) {
		const Tuple * tuple = req_tuple(args + 0);
		return tuple->unsafe_front();
	}



	Value tuple_back::func(Context *, const Value * args) {
		const Tuple * tuple = req_tuple(args + 0);
		return tuple->unsafe_back();
	}



	Value tuple_values::func(Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		Tuple * tuple = req_tuple(args + 0);
		Array * array = core->heap.make<Array>(tuple->get_underlying());
		return value::array(array);
	}
}