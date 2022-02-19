#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "cast.hxx"
#include "index.hxx"

namespace ltn::vm {
	namespace {
		auto iterator(auto i) {
			return Value(static_cast<std::int64_t>(i));
		}
	}

	void LtnVM::begin() {
		const auto ref = this->reg.pop();
		if(isArr(ref)) {
			this->reg.push(iterator(0));
			return;
		}

		if(isRange(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(iterator(range.begin));
			return;
		}

		throw except::invalidArgument();
	}


	void LtnVM::end() {
		const auto ref = this->reg.pop();
		if(isArr(ref)) {
			const auto & array = this->heap.read<Array>(ref.u);
			this->reg.push(iterator(array.arr.size()));
			return;
		}

		if(isRange(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(iterator(range.end));
			return;
		}

		throw except::invalidArgument();
	}
}