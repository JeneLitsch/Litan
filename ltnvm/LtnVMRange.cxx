#include "LtnVM.hxx"
#include "type_check.hxx"
#include "convert.hxx"
#include "index.hxx"

namespace ltn::vm {
	namespace {
		auto iterator(auto i) {
			return Value(static_cast<std::int64_t>(i));
		}
	}

	void LtnVM::begin() {
		const auto ref = this->core.reg.pop();
		if(is_array(ref)) {
			this->core.reg.push(iterator(0));
			return;
		}

		if(is_range(ref)) {
			const auto & range = this->core.heap.read<Range>(ref.u);
			this->core.reg.push(iterator(range.begin));
			return;
		}

		throw except::invalid_argument();
	}


	void LtnVM::end() {
		const auto ref = this->core.reg.pop();
		if(is_array(ref)) {
			const auto & array = this->core.heap.read<Array>(ref.u);
			this->core.reg.push(iterator(array.arr.size()));
			return;
		}

		if(is_range(ref)) {
			const auto & range = this->core.heap.read<Range>(ref.u);
			this->core.reg.push(iterator(range.end));
			return;
		}

		throw except::invalid_argument();
	}
}