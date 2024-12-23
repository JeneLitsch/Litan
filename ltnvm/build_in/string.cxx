#include "string.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltn/utf8.hxx"
#include "ltnvm/stdlib/string.hxx"

namespace ltn::vm::build_in {


	Value to_string(VMCore & core) {
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
				substrs.push_back(String{string.substr(last, next-last)});
				last = next + delim.size();
				next = string.find(delim, last);
			}
			substrs.push_back(String{string.substr(last, next-last)});
			return substrs;
		}
	}


	Value split_string(VMCore & core) {
		const auto val_delim = core.stack.pop();
		const auto val_string = core.stack.pop();
		return call<stdlib::string_split>(core, { val_string, val_delim });
		if(!is_string(val_string) || !is_string(val_delim)) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::split expected 2 strings."
			};
		}
		const auto & string = *value::as<String>(val_string);
		const auto & delim = *value::as<String>(val_delim);
		Array * segments = core.heap.alloc<Array>({});

			
		if(string.empty()) return value::array(segments);
		if(delim.empty()) {
			for(std::int64_t i = 0; i < string.size(); i++) {
				std::string utf_character = utf8::encode_char(string.at(i));
				String * sub_string = core.heap.alloc(String{std::move(utf_character)}); 
				segments->push_back(value::string(sub_string));
			}
		}
		else {
			for(auto && str : split_impl(string.copy_to_std_string(), delim.copy_to_std_string())) {
				segments->push_back(value::string(core.heap.alloc(String{std::move(str)})));
			}

		}
		return value::array(segments);
	}



	Value chr(VMCore & core) {
		const auto arg = core.stack.pop();
		if(!is_int(arg)) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::chr expected int."
			};
		}
		String * str = core.heap.make<String>(utf8::encode_char(static_cast<std::uint32_t>(arg.i)));
		return value::string(str);
	}




	Value ord(VMCore & core) {
		const auto arg = core.stack.pop();
		if(!is_string(arg)) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::ord expected string."
			};
		}
		String * str = value::as<String>(arg);
		if(str->empty()) {
			throw Exception {
				Exception::Type::INVALID_ARGUMENT,
				"std::ord expected non-empty string."
			};
		}
		return value::integer(static_cast<std::int64_t>(str->at(0)));
	}



	Value parse_bool(VMCore &) {
		return value::null;
	}



	Value parse_char(VMCore &) {
		return value::null;
	}



	Value parse_int(VMCore &) {
		return value::null;
	}



	Value parse_float(VMCore &) {
		return value::null;
	}	
}