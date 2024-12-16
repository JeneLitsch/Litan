#include "string.hxx"
#include "ltnvm/objects/container/String.hxx"

namespace ltn::vm::stdlib {
	Value string_size::func(Context *, const Value * args) {
		String * string = req_string(args + 0);
		return value::integer(string->size());
	}

	Value string_is_empty::func(Context * context, const Value * args) {
		return value::boolean(string_size::func(context, args).i == 0);
	}
}