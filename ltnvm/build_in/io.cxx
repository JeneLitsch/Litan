#include "io.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::build_in {
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