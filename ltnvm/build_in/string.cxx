#include "string.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/stringify.hxx"

namespace ltn::vm::build_in {


	Value to_string(VmCore & core) {
		const auto input = core.stack.pop();
		const auto address = core.heap.alloc<String>({stringify(input, core.heap)});
		return value::string(address);
	}


	namespace {
		std::vector<std::string> split_impl(
			const std::string & string,
			const std::string & delim) {
			
			std::vector<std::string> substrs;
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
		const auto & string = core.heap.read<String>(val_string).get();
		const auto & delim = core.heap.read<String>(val_delim).get();
		const auto segments_ptr = core.heap.alloc<Array>({});
		auto & segments = core.heap.read<Array>(segments_ptr).get();

		if(delim.empty()) return value::array(segments_ptr);
		if(string.empty()) return value::array(segments_ptr);

		for(auto && str : split_impl(string, delim)) {
			segments.push_back(value::string(core.heap.alloc(String{std::move(str)})));
		}

		return value::array(segments_ptr);
	}



	Value join_string(VmCore & core) {
		auto val_joiner = core.stack.pop();
		auto val_array = core.stack.pop();
		if(!is_array(val_array) || !is_string(val_joiner)) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::join expected 1 array and 1 string."
			};
		}
		std::ostringstream joined_string;
		const auto & array = core.heap.read<Array>(val_array).get();
		const auto & joiner = core.heap.read<String>(val_joiner).get();
		bool first = true;
		for(const auto & val_str : array) {
			if(first) {
				first = false;
			}
			else {
				joined_string << joiner;
			}
			if(!is_string(val_str)) {
				if(!is_string(val_array) || !is_string(val_joiner)) {
					throw Exception {
						Exception::Type::INVALID_ARGUMENT,
						"std::join. Each array elements must be a string."
					};
				}
			}
			joined_string << core.heap.read<String>(val_str).get();
		}
		return value::string(core.heap.alloc(String{joined_string.str()}));
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