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
		const auto ref = this->reg.pop();
		if(is_array(ref)) {
			this->reg.push(iterator(0));
			return;
		}

		if(is_range(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(iterator(range.begin));
			return;
		}

		throw except::invalid_argument();
	}


	void LtnVM::end() {
		const auto ref = this->reg.pop();
		if(is_array(ref)) {
			const auto & array = this->heap.read<Array>(ref.u);
			this->reg.push(iterator(array.arr.size()));
			return;
		}

		if(is_range(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(iterator(range.end));
			return;
		}

		throw except::invalid_argument();
	}
}