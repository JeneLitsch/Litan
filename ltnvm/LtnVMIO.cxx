#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "Stringify.hxx"

namespace ltn::vm {
	void LtnVM::out() {
		const auto value = this->reg.pop();
		const auto ref = this->reg.pop();
		if(isOStream(ref)) {
			auto & ostream = this->heap.read<OStream>(ref.u).get();
			ostream << toString(value, this->heap); 
		}
		else {
			throw std::runtime_error{"Can only output to ostream"};
		}
	}

	namespace {
		using VT = Value::Type;

		std::istream & getIstream(Heap & heap, Register & reg) {
			const auto ref = reg.pop();
			if(isIStream(ref)) {
				return heap.read<IStream>(ref.u).get();
			}
			else {
				throw std::runtime_error{"Can only read from istream"};
			}
		}
	}

	void LtnVM::in_str() {
		auto & in = getIstream(this->heap, this->reg); 
		std::string value;
		in >> value;
		const auto addr = heap.alloc<String>({value});
		reg.push(Value{addr, VT::STRING});
	}

	void LtnVM::in_line() {
		auto & in = getIstream(this->heap, this->reg); 
		std::string value;
		std::getline(in, value);
		const auto addr = heap.alloc<String>({value});
		reg.push(Value{addr, VT::STRING});
	}

	void LtnVM::in_int() {
		auto & in = getIstream(this->heap, this->reg); 
		std::int64_t value;
		in >> value;
		reg.push(Value{value});
	}

	void LtnVM::in_float() {
		auto & in = getIstream(this->heap, this->reg); 
		double value;
		in >> value;
		reg.push(Value{value});
	}

	void LtnVM::is_eof() {
		auto & in = getIstream(this->heap, this->reg); 
		reg.push(Value{in.eof()});
	}
}