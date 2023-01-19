#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/cast.hxx"
#include "ltnvm/stringify.hxx"
#include <fstream>

namespace ltn::vm::inst {
	void out(VmCore & core) {
		const auto value = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_ostream(ref)) {
			auto & ostream = core.heap.read<OStream>(ref.u).get();
			ostream << stringify(value, core.heap); 
		}
		else {
			throw except::not_output();
		}
	}


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
	}


	void in_str(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		std::string value;
		in >> value;
		const auto addr = core.heap.alloc<String>(std::move(value));
		core.stack.push(Value{addr, VT::STRING});
	}



	void in_line(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		std::string value;
		std::getline(in, value);
		const auto addr = core.heap.alloc<String>(std::move(value));
		core.stack.push(Value{addr, VT::STRING});
	}



	void in_bool(VmCore & core) {
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

		core.stack.push(value::boolean(value));
	}



	void in_char(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		char value;
		in >> value;
		core.stack.push(value::character(value));
	}



	void in_int(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		std::int64_t value;
		in >> value;
		core.stack.push(value::integer(value));
	}



	void in_float(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		stx::float64_t value;
		in >> value;
		core.stack.push(value::floating(value));
	}



	void in_all(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack);
		std::ostringstream oss;
		oss << in.rdbuf();
		const auto ref = core.heap.alloc<String>(oss.str());
		core.stack.push(value::string(ref));
	}



	void is_eof(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		core.stack.push(Value{in.eof()});
	}



	void is_good(VmCore & core) {
		auto & in = get_istream(core.heap, core.stack); 
		core.stack.push(value::boolean(static_cast<bool>(in)));
	}


	
	void close_stream(VmCore & core) {
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
	}
}