#include "string.hxx"
#include "litan_vm/objects/container/String.hxx"
#include "litan_vm/VMCore.hxx"
#include "litan_core/utf8.hxx"

namespace ltn::vm::stdlib {
	Value string_size::func(Context *, const Value * args) {
		String * string = req_string(args + 0);
		return value::integer(string->size());
	}



	Value string_is_empty::func(Context * context, const Value * args) {
		return value::boolean(string_size::func(context, args).i == 0);
	}



	Value string_split::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);

		const String * string = req_string(args + 0);
		const String * delim = req_string(args + 1);

		Array * segments = core.heap.alloc<Array>({});

			
		if(string->empty()) return value::array(segments);
		if(delim->empty()) {
			for(std::int64_t i = 0; i < string->size(); i++) {
				std::string utf_character = utf8::encode_char(string->at(i));
				String * sub_string = core.heap.alloc(String{std::move(utf_character)}); 
				segments->push_back(value::string(sub_string));
			}
		}
		else {
			const std::string_view string_sv = *string;
			const std::string_view delim_sv = *delim;
			std::size_t last = 0;
			std::size_t next = string_sv.find(*delim, last);
			auto emit = [&] () {
				auto sub_string_data = std::string{string_sv.substr(last, next-last)};
				segments->push_back(value::string(core.heap.make<String>(sub_string_data)));
			};
			while (next != std::string::npos) {
				emit();
				last = next + delim_sv.size();
				next = string_sv.find(*delim, last);
			}
			emit();
		}
		return value::array(segments);
	}
}