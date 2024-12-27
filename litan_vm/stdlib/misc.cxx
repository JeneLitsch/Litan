#include "misc.hxx"
#include "litan_core/utf8.hxx"
#include "litan_vm/utils/stringify.hxx"

namespace ltn::vm::stdlib {
	Value ord::func(Context * context, const Value * args) {
		if(!is_string(args[0])) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::ord expected string."
			};
		}
		String * str = value::as<String>(args[0]);
		if(str->empty()) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::ord expected non-empty string."
			};
		}
		return value::integer(static_cast<std::int64_t>(str->at(0)));
	}



	Value chr::func(Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		if(!is_int(args[0])) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::chr expected int."
			};
		}
		String * str = core->heap.make<String>(utf8::encode_char(static_cast<std::uint32_t>(args[0].i)));
		return value::string(str);
	}



	Value str::func(Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		return value::string(core->heap.make<String>(stringify(args[0], *core)));
	}


	Value call_stack_depth::func(Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		return value::integer(core->stack.depth());
	}
}