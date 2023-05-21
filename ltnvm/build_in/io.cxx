#include <fstream>
#include <filesystem>
#include "io.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/stringify.hxx"
#include "ltnvm/convert.hxx"

namespace ltn::vm::build_in::io {
	namespace {
		using VT = Value::Type;

		std::istream & get_istream(Heap & heap, Stack & stack) {
			const auto ref = stack.pop();
			if(is_istream(ref)) {
				return heap.read<IStream>(ref.u).get();
			}
			else {
				throw except::not_input();
			}
		}

		template<typename T>
		auto add_out (VmCore & core, T && out) {
			const auto ptr = core.heap.alloc<OStream>(std::forward<T>(out));
			Value val{ptr, Value::Type::OSTREAM};
			core.heap.collect_garbage(core.stack, core.static_variables, val);
			return val;
		};



		template<typename T>
		Value add_in (VmCore & core, T && in) {
			const auto ptr = core.heap.alloc<IStream>(std::forward<T>(in));
			Value val{ptr, Value::Type::ISTREAM};
			core.heap.collect_garbage(core.stack, core.static_variables, val);
			return val;
		};
	}




	Value cout(VmCore & core) {
		return add_out(core, OStream{std::cout});
	}



	Value fout(VmCore & core) {
		const auto openmode = convert::to_int(core.stack.pop());
		const auto ref = core.stack.pop();
		if(!is_string(ref)) throw except::invalid_argument();
		
		const auto & path = core.heap.read<String>(ref.u);

		const auto flags = openmode ? std::ios::app : std::ios::trunc;

		auto fout = std::make_unique<std::ofstream>(path, flags);
		return add_out(core, OStream{std::move(fout)});
	}



	Value strout(VmCore & core) {
		return add_out(core, OStream{std::make_unique<std::ostringstream>()});
	}



	Value cin(VmCore & core) {
		return add_in(core, IStream{std::cin});
	}



	Value fin(VmCore & core) {
		const auto ref = core.stack.pop();
		if(!is_string(ref)) {
			throw except::invalid_argument();
		}
		const auto & path = core.heap.read<String>(ref.u);
		if(!std::filesystem::exists(path)) {
			throw except::cannot_open_file(path);
		}
		return add_in(core, IStream{std::make_unique<std::ifstream>(path)});
	}



	Value strin(VmCore & core) {
		const auto ref = core.stack.pop();
		if(!is_string(ref)) throw except::invalid_argument();
		const auto & str = core.heap.read<String>(ref.u);
		return add_in(core, IStream{std::make_unique<std::istringstream>(str)});
	}



	Value close_stream(VmCore & core) {
		const auto ref = core.stack.pop();
		if(is_ostream(ref)) {
			auto & ostream = core.heap.read<OStream>(ref.u).get();
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
			auto & istream = core.heap.read<IStream>(ref.u).get();
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



	Value is_eof(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		return value::boolean(in.peek() == EOF);
	}




	Value print(VmCore & core) {
		const auto value = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_ostream(ref)) {
			auto & ostream = core.heap.read<OStream>(ref.u).get();
			ostream << stringify(value, core); 
			return value::null;
		}
		else {
			throw except::not_output();
		}
	}



	Value read_str(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		std::string value;
		in >> value;
		if(in) {
			auto ref = core.heap.alloc<String>(std::move(value));
			return value::string(ref);
		}
		else {
			in.clear();
			return value::null;
		}
	}



	Value read_line(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		std::string value;
		std::getline(in, value);
		if(in) {
			auto ref = core.heap.alloc<String>(std::move(value));
			return value::string(ref);
		}
		else {
			in.clear();
			return value::null;
		}
	}



	Value read_bool(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack);
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



	Value read_char(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
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



	Value read_int(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
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



	Value read_float(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
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



	Value read_all(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack);
		std::ostringstream oss;
		oss << in.rdbuf();
		const auto ref = core.heap.alloc<String>(oss.str());
		return value::string(ref);
	}



	Value set_fg_color(VmCore & core) {
		const auto color = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_ostream(ref) && is_int(color)) {
			auto & out = core.heap.read<OStream>(ref.u).get();
			out	<< "\u001b[3" << color.i % 8; 
			if(color.i >= 8) out << ";1";
			out << "m";
			return value::null;
		}
		else throw except::invalid_argument();
	}



	Value set_bg_color(VmCore & core) {
		const auto color = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_ostream(ref) && is_int(color)) {
			auto & out = core.heap.read<OStream>(ref.u).get();
			out	<< "\u001b[4" << color.i % 8;
			if(color.i >= 8) out << ";1";
			out << "m";
			return value::null;
		}
		else throw except::invalid_argument();
	}



	Value reset_color(VmCore & core) {
		const auto ref = core.stack.pop();
		if(is_ostream(ref)) {
			auto & out = core.heap.read<OStream>(ref.u).get();
			out	<< "\u001b[0m";
			return value::null;
		}
		else throw except::invalid_argument();
	}
}