#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "cast.hxx"

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


	void LtnVM::is_eof() {
		auto & in = get_istream(this->heap, this->reg); 
		reg.push(Value{in.eof()});
	}


	void LtnVM::is_good() {
		auto & in = get_istream(this->heap, this->reg); 
		reg.push(value::boolean(static_cast<bool>(in)));
	}
}