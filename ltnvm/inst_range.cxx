#include "instructions.hxx"
#include "type_check.hxx"
#include "convert.hxx"
#include "index.hxx"

namespace ltn::vm::inst {
	namespace {
		auto iterator(auto i) {
			return Value(static_cast<std::int64_t>(i));
		}
	}

	void begin(VmCore & core) {
		const auto ref = core.reg.pop();
		if(is_array(ref)) {
			core.reg.push(iterator(0));
			return;
		}

		if(is_range(ref)) {
			const auto & range = core.heap.read<Range>(ref.u);
			core.reg.push(iterator(range.begin));
			return;
		}

		throw except::invalid_argument();
	}


	void end(VmCore & core) {
		const auto ref = core.reg.pop();
		if(is_array(ref)) {
			const auto & array = core.heap.read<Array>(ref.u);
			core.reg.push(iterator(array.arr.size()));
			return;
		}

		if(is_range(ref)) {
			const auto & range = core.heap.read<Range>(ref.u);
			core.reg.push(iterator(range.end));
			return;
		}

		throw except::invalid_argument();
	}
}