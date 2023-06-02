#include "string.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {


	Value to_string(VmCore & core) {
		const auto input = core.stack.pop();
		const auto address = core.heap.alloc<String>({stringify(input, core)});
		return value::string(address);
	}


	namespace {
		std::vector<String> split_impl(
			const std::string & string,
			const std::string & delim) {
			
			std::vector<String> substrs;
			std::size_t last = 0;
			std::size_t next = string.find(delim, last);
			while (next != std::string::npos) {
				substrs.push_back(string.substr(last, next-last));
				last = next + delim.size();
				next = string.find(delim, last);
			}
			substrs.push_back(string.substr(last, next-last));
			return substrs;
		}
	}


	Value split_string(VmCore & core) {
		const auto val_delim = core.stack.pop();
		const auto val_string = core.stack.pop();
		if(!is_string(val_string) || !is_string(val_delim)) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::split expected 2 strings."
			};
		}
		const auto & string = core.heap.read<String>(val_string.u);
		const auto & delim = core.heap.read<String>(val_delim.u);
		const auto segments_ptr = core.heap.alloc<Array>({});
		auto & segments = core.heap.read<Array>(segments_ptr);

		if(delim.empty()) return value::array(segments_ptr);
		if(string.empty()) return value::array(segments_ptr);

		for(auto && str : split_impl(string, delim)) {
			segments.push_back(value::string(core.heap.alloc<String>(std::move(str))));
		}

		return value::array(segments_ptr);
	}



	Value parse_bool(VmCore &) {
		return value::null;
	}



	Value parse_char(VmCore &) {
		return value::null;
	}



	Value parse_int(VmCore &) {
		return value::null;
	}



	Value parse_float(VmCore &) {
		return value::null;
	}	
}