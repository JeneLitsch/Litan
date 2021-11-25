#include "LtnVM.hxx"
#include "TypeCheck.hxx"

namespace ltn::vm {
	void LtnVM::size() {
		const auto ref = this->reg.pop();
		if (isArr(ref)) {
			const auto & arr = this->heap.readArray(ref.u);
			this->reg.push(static_cast<std::int64_t>(arr.size()));
		}
		else if(isStr(ref)) {
			const auto & str = this->heap.readString(ref.u);
			this->reg.push(static_cast<std::int64_t>(str.size()));
		}
		else {
			this->reg.push(static_cast<std::int64_t>(0));
		}
	}

	void LtnVM::front() {
		const auto ref = this->reg.pop();
		if (isArr(ref)) {
			const auto & arr = this->heap.readArray(ref.u);
			this->reg.push(arr.front());
		}
		else {
			throw std::runtime_error{"Cannot get front element from non array type"};
		}
	}

	void LtnVM::back() {
		const auto ref = this->reg.pop();
		if (isArr(ref)) {
			const auto & arr = this->heap.readArray(ref.u);
			this->reg.push(arr.back());
		}
		else {
			throw std::runtime_error{"Cannot get back element from non array type"};
		}
	}
}