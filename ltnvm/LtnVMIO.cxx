#include "LtnVM.hxx"
#include "type_check.hxx"
#include "cast.hxx"
#include <fstream>

namespace ltn::vm {
	void LtnVM::out() {
		const auto value = this->reg.pop();
		const auto ref = this->reg.pop();
		if(is_ostream(ref)) {
			auto & ostream = this->heap.read<OStream>(ref.u).get();
			ostream << cast::to_string(value, this->heap); 
		}
		else {
			throw except::not_output();
		}
	}


	void LtnVM::stylize() {
		const auto func = this->fetch_byte();
			switch (func) {

			case 0: {
				const auto color = this->reg.pop();
				const auto ref = this->reg.pop();
				if(is_ostream(ref) && is_int(color)) {
					auto & out = this->heap.read<OStream>(ref.u).get();
					out	<< "\u001b[3" << color.i % 8; 
					if(color.i >= 8) out << ";1";
					out << "m";
				}
				else throw except::invalid_argument();
			} break;

			case 1: {
				const auto color = this->reg.pop();
				const auto ref = this->reg.pop();
				if(is_ostream(ref) && is_int(color)) {
					auto & out = this->heap.read<OStream>(ref.u).get();
					out	<< "\u001b[4" << color.i % 8;
					if(color.i >= 8) out << ";1";
					out << "m";
				}
				else throw except::invalid_argument();
			} break;


			case 2: {
				const auto ref = this->reg.pop();
				if(is_ostream(ref)) {
					auto & out = this->heap.read<OStream>(ref.u).get();
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
		auto & in = get_istream(this->heap, this->reg); 
		std::string value;
		in >> value;
		const auto addr = heap.alloc<String>({value});
		reg.push(Value{addr, VT::STRING});
	}


	void LtnVM::in_line() {
		auto & in = get_istream(this->heap, this->reg); 
		std::string value;
		std::getline(in, value);
		const auto addr = heap.alloc<String>({value});
		reg.push(Value{addr, VT::STRING});
	}


	void LtnVM::in_bool() {
		auto & in = get_istream(this->heap, this->reg);
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

		reg.push(value::boolean(value));
	}


	void LtnVM::in_char() {
		auto & in = get_istream(this->heap, this->reg); 
		char value;
		in >> value;
		reg.push(value::character(value));
	}


	void LtnVM::in_int() {
		auto & in = get_istream(this->heap, this->reg); 
		std::int64_t value;
		in >> value;
		reg.push(value::integer(value));
	}


	void LtnVM::in_float() {
		auto & in = get_istream(this->heap, this->reg); 
		stx::float64_t value;
		in >> value;
		reg.push(value::floating(value));
	}

	void LtnVM::in_all() {
		auto & in = get_istream(this->heap, this->reg);
		std::ostringstream oss;
		oss << in.rdbuf();
		const auto ref = heap.alloc<String>({oss.str()});
		reg.push(value::string(ref));
	}

	void LtnVM::is_eof() {
		auto & in = get_istream(this->heap, this->reg); 
		reg.push(Value{in.eof()});
	}


	void LtnVM::is_good() {
		auto & in = get_istream(this->heap, this->reg); 
		reg.push(value::boolean(static_cast<bool>(in)));
	}

	
	void LtnVM::close_stream() {
		const auto ref = this->reg.pop();
		if(is_ostream(ref)) {
			auto & ostream = this->heap.read<OStream>(ref.u).get();
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
			auto & istream = this->heap.read<IStream>(ref.u).get();
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