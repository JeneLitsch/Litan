#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/cast.hxx"
#include <fstream>

namespace ltn::vm::inst {
	void out(VmCore & core) {
		const auto value = core.reg.pop();
		const auto ref = core.reg.pop();
		if(is_ostream(ref)) {
			auto & ostream = core.heap.read<OStream>(ref.u).get();
			ostream << cast::to_string(value, core.heap); 
		}
		else {
			throw except::not_output();
		}
	}


	void stylize(VmCore & core) {
		const auto func = core.fetch_byte();
			switch (func) {

			case 0: {
				const auto color = core.reg.pop();
				const auto ref = core.reg.pop();
				if(is_ostream(ref) && is_int(color)) {
					auto & out = core.heap.read<OStream>(ref.u).get();
					out	<< "\u001b[3" << color.i % 8; 
					if(color.i >= 8) out << ";1";
					out << "m";
				}
				else throw except::invalid_argument();
			} break;

			case 1: {
				const auto color = core.reg.pop();
				const auto ref = core.reg.pop();
				if(is_ostream(ref) && is_int(color)) {
					auto & out = core.heap.read<OStream>(ref.u).get();
					out	<< "\u001b[4" << color.i % 8;
					if(color.i >= 8) out << ";1";
					out << "m";
				}
				else throw except::invalid_argument();
			} break;


			case 2: {
				const auto ref = core.reg.pop();
				if(is_ostream(ref)) {
					auto & out = core.heap.read<OStream>(ref.u).get();
					out	<< "\u001b[0m";
				}
				else throw except::invalid_argument();
			} break;

			default:
				throw except::invalid_argument();
				break;
		}
	}



	namespace {
		using VT = Value::Type;

		std::istream & get_istream(Heap & heap, Register & reg) {
			const auto ref = reg.pop();
			if(is_istream(ref)) {
				return heap.read<IStream>(ref.u).get();
			}
			else {
				throw except::not_input();
			}
		}
	}


	void in_str(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg); 
		std::string value;
		in >> value;
		const auto addr = core.heap.alloc<String>({value});
		core.reg.push(Value{addr, VT::STRING});
	}


	void in_line(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg); 
		std::string value;
		std::getline(in, value);
		const auto addr = core.heap.alloc<String>({value});
		core.reg.push(Value{addr, VT::STRING});
	}


	void in_bool(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg);
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

		core.reg.push(value::boolean(value));
	}


	void in_char(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg); 
		char value;
		in >> value;
		core.reg.push(value::character(value));
	}


	void in_int(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg); 
		std::int64_t value;
		in >> value;
		core.reg.push(value::integer(value));
	}


	void in_float(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg); 
		stx::float64_t value;
		in >> value;
		core.reg.push(value::floating(value));
	}

	void in_all(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg);
		std::ostringstream oss;
		oss << in.rdbuf();
		const auto ref = core.heap.alloc<String>({oss.str()});
		core.reg.push(value::string(ref));
	}

	void is_eof(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg); 
		core.reg.push(Value{in.eof()});
	}


	void is_good(VmCore & core) {
		auto & in = get_istream(core.heap, core.reg); 
		core.reg.push(value::boolean(static_cast<bool>(in)));
	}

	
	void close_stream(VmCore & core) {
		const auto ref = core.reg.pop();
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
	}
}