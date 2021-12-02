#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "Stringify.hxx"

namespace ltn::vm {
	void LtnVM::to_seconds() {
		const auto ref = this->reg.pop();
		if (isClock(ref)) {
			const auto & clock = this->heap.read<Clock>(ref.u);
			this->reg.push(clock.getSeconds());
		}
		else {
			throw std::runtime_error{"Can only convert clock to seconds"};
		}
	}
}