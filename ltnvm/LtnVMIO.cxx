#include "LtnVM.hxx"
#include "type_check.hxx"
#include "cast.hxx"
#include <fstream>

namespace ltn::vm {
	void LtnVM::out() {
		const auto value = this->core.reg.pop();
		const auto ref = this->core.reg.pop();
		if(is_ostream(ref)) {
			auto & ostream = this->core.heap.read<OStream>(ref.u).get();
			ostream << cast::to_string(value, this->core.heap); 
		}
		else {
			throw except::not_output();
		}
	}


	void LtnVM::stylize() {
		const auto func = this->fetch_byte();
			switch (func) {

			case 0: {
				const auto color = this->core.reg.pop();
				const auto ref = this->core.reg.pop();
				if(is_ostream(ref) && is_int(color)) {
					auto & out = this->core.heap.read<OStream>(ref.u).get();
					out	<< "\u001b[3" << color.i % 8; 
					if(color.i >= 8) out << ";1";
					out << "m";
				}
				else throw except::invalid_argument();
			} break;

			case 1: {
				const auto color = this->core.reg.pop();
				const auto ref = this->core.reg.pop();
				if(is_ostream(ref) && is_int(color)) {
					auto & out = this->core.heap.read<OStream>(ref.u).get();
					out	<< "\u001b[4" << color.i % 8;
					if(color.i >= 8) out << ";1";
					out << "m";
				}
				else throw except::invalid_argument();
			} break;


			case 2: {
				const auto ref = this->core.reg.pop();
				if(is_ostream(ref)) {
					auto & out = this->core.heap.read<OStream>(ref.u).get();
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


	void LtnVM::in_str() {
		auto & in = get_istream(this->core.heap, this->core.reg); 
		std::string value;
		in >> value;
		const auto addr = this->core.heap.alloc<String>({value});
		this->core.reg.push(Value{addr, VT::STRING});
	}


	void LtnVM::in_line() {
		auto & in = get_istream(this->core.heap, this->core.reg); 
		std::string value;
		std::getline(in, value);
		const auto addr = this->core.heap.alloc<String>({value});
		this->core.reg.push(Value{addr, VT::STRING});
	}


	void LtnVM::in_bool() {
		auto & in = get_istream(this->core.heap, this->core.reg);
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

		this->core.reg.push(value::boolean(value));
	}


	void LtnVM::in_char() {
		auto & in = get_istream(this->core.heap, this->core.reg); 
		char value;
		in >> value;
		this->core.reg.push(value::character(value));
	}


	void LtnVM::in_int() {
		auto & in = get_istream(this->core.heap, this->core.reg); 
		std::int64_t value;
		in >> value;
		this->core.reg.push(value::integer(value));
	}


	void LtnVM::in_float() {
		auto & in = get_istream(this->core.heap, this->core.reg); 
		stx::float64_t value;
		in >> value;
		this->core.reg.push(value::floating(value));
	}

	void LtnVM::in_all() {
		auto & in = get_istream(this->core.heap, this->core.reg);
		std::ostringstream oss;
		oss << in.rdbuf();
		const auto ref = this->core.heap.alloc<String>({oss.str()});
		this->core.reg.push(value::string(ref));
	}

	void LtnVM::is_eof() {
		auto & in = get_istream(this->core.heap, this->core.reg); 
		this->core.reg.push(Value{in.eof()});
	}


	void LtnVM::is_good() {
		auto & in = get_istream(this->core.heap, this->core.reg); 
		this->core.reg.push(value::boolean(static_cast<bool>(in)));
	}

	
	void LtnVM::close_stream() {
		const auto ref = this->core.reg.pop();
		if(is_ostream(ref)) {
			auto & ostream = this->core.heap.read<OStream>(ref.u).get();
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
			auto & istream = this->core.heap.read<IStream>(ref.u).get();
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