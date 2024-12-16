#include <fstream>
#include <filesystem>
#include "io.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/utils/convert.hxx"

namespace ltn::vm::build_in::io {
	namespace {
		using VT = ValueType;

		std::istream & pop_istream(VMStack & stack) {
			const auto ref = stack.pop();
			if(is_istream(ref)) {
				return value::as<IStream>(ref)->get();
			}
			else {
				throw except::not_input();
			}
		}



		template<typename T>
		auto add_out (VMCore & core, T && out) {
			core.heap.collect_garbage(core.stack);
			const auto ptr = core.heap.alloc<OStream>(std::forward<T>(out));
			return value::ostream(ptr);
		}



		template<typename T>
		Value add_in (VMCore & core, T && in) {
			core.heap.collect_garbage(core.stack);
			const auto ptr = core.heap.alloc<IStream>(std::forward<T>(in));
			return value::istream(ptr);
		}
	}




	Value cout(VMCore & core) {
		return add_out(core, OStream{std::cout});
	}



	Value fout(VMCore & core) {
		const auto openmode = convert::to_int(core.stack.pop());
		const auto ref = core.stack.pop();
		if(!is_string(ref)) throw except::invalid_argument();
		
		const String * path = value::as<String>(ref);
		auto path_str = path->copy_to_std_string(); 

		const auto flags = openmode ? std::ios::app : std::ios::trunc;

		auto fout = std::make_unique<std::ofstream>(path_str, flags);
		return add_out(core, OStream{std::move(fout)});
	}



	Value strout(VMCore & core) {
		return add_out(core, OStream{std::make_unique<std::ostringstream>()});
	}



	Value cin(VMCore & core) {
		return add_in(core, IStream{std::cin});
	}



	Value fin(VMCore & core) {
		const auto ref = core.stack.pop();
		if(!is_string(ref)) {
			throw except::invalid_argument();
		}
		const String * path = value::as<String>(ref);
		auto path_str = path->copy_to_std_string(); 
		if(!std::filesystem::exists(path_str)) {
			throw except::cannot_open_file(path_str);
		}
		return add_in(core, IStream{std::make_unique<std::ifstream>(path_str)});
	}



	Value strin(VMCore & core) {
		const auto ref = core.stack.pop();
		if(!is_string(ref)) throw except::invalid_argument();
		const String * str = value::as<String>(ref);
		return add_in(core, IStream{std::make_unique<std::istringstream>(str->copy_to_std_string())});
	}



	Value close_stream(VMCore & core) {
		const auto ref = core.stack.pop();
		if(is_ostream(ref)) {
			std::ostream & ostream = value::as<OStream>(ref)->get();
			if(auto * out = dynamic_cast<std::ofstream *>(&ostream)) {
				out->close();
			}
			else {
				throw Exception{
					Exception::Type::INVALID_ARGUMENT,
					"Not an ofstream"};
			}
		}

		else if(is_istream(ref)) {
			std::istream & istream = value::as<IStream>(ref)->get();
			if(auto * in = dynamic_cast<std::ifstream *>(&istream)) {
				in->close();
			}
			else {
				throw Exception{
					Exception::Type::INVALID_ARGUMENT,
					"Not an ifstream"};
			}
		}

		else {
			throw Exception{
				Exception::Type::INVALID_ARGUMENT,
				"Not a stream"};
		}
		return value::null;
	}



	Value is_eof(VMCore & core) {
		auto & in = pop_istream(core.stack); 
		return value::boolean(in.peek() == EOF);
	}




	Value print(VMCore & core) {
		const auto value = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_ostream(ref)) {
			std::ostream & ostream = value::as<OStream>(ref)->get();
			ostream << stringify(value, core); 
			return value::null;
		}
		else {
			throw except::not_output();
		}
	}



	Value read_str(VMCore & core) {
		auto & in = pop_istream(core.stack); 
		std::string value;
		in >> value;
		if(in) {
			auto ref = core.heap.alloc(String{std::move(value)});
			return value::string(ref);
		}
		else {
			in.clear();
			return value::null;
		}
	}



	Value read_line(VMCore & core) {
		auto & in = pop_istream(core.stack); 
		std::string value;
		std::getline(in, value);
		if(in) {
			auto ref = core.heap.alloc(String{std::move(value)});
			return value::string(ref);
		}
		else {
			in.clear();
			return value::null;
		}
	}



	Value read_bool(VMCore & core) {
		auto & in = pop_istream(core.stack);
		bool value;
		in >> std::ws;

		if(in.peek() == '0') {
			value = false;
			in.ignore();
		}
		
		else if(in.peek() == '1') {
			value = true;
			in.ignore();
		}
		
		else  {
			in >> std::boolalpha >> value >> std::noboolalpha;
		}

		if(in) {
			return value::boolean(value);
		}
		else {
			in.clear();
			return value::null;
		}
	}



	Value read_char(VMCore & core) {
		auto & in = pop_istream(core.stack); 
		char value;
		in >> value;
		if(in) {
			return value::character(value);
		}
		else {
			in.clear();
			return value::null;
		}
	}



	Value read_int(VMCore & core) {
		auto & in = pop_istream(core.stack); 
		std::int64_t value;
		in >> value;
		if(in) {
			return value::integer(value);
		}
		else {
			in.clear();
			return value::null;
		}
	}



	Value read_float(VMCore & core) {
		auto & in = pop_istream(core.stack); 
		stx::float64_t value;
		in >> value;
		if(in) {
			return value::floating(value);
		}
		else {
			in.clear();
			return value::null;
		}
	}



	Value read_all(VMCore & core) {
		auto & in = pop_istream(core.stack);
		std::ostringstream oss;
		oss << in.rdbuf();
		const auto ref = core.heap.alloc(String{oss.str()});
		return value::string(ref);
	}



	Value set_fg_color(VMCore & core) {
		const auto color = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_ostream(ref) && is_int(color)) {
			std::ostream & out = value::as<OStream>(ref)->get();
			out	<< "\u001b[3" << color.i % 8; 
			if(color.i >= 8) out << ";1";
			out << "m";
			return value::null;
		}
		else throw except::invalid_argument();
	}



	Value set_bg_color(VMCore & core) {
		const auto color = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_ostream(ref) && is_int(color)) {
			std::ostream & out = value::as<OStream>(ref)->get();
			out	<< "\u001b[4" << color.i % 8;
			if(color.i >= 8) out << ";1";
			out << "m";
			return value::null;
		}
		else throw except::invalid_argument();
	}



	Value reset_color(VMCore & core) {
		const auto ref = core.stack.pop();
		if(is_ostream(ref)) {
			std::ostream & out = value::as<OStream>(ref)->get();
			out	<< "\u001b[0m";
			return value::null;
		}
		else throw except::invalid_argument();
	}
}