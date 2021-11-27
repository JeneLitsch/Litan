#include "LtnVM.hxx"
#include "TypeCheck.hxx"

namespace ltn::vm {
	void LtnVM::read() {
		const auto addr = this->reg.pop();
		const auto value = this->stack.read(addr.u);
		this->reg.push(value);
	}

	void LtnVM::write() {
		const auto addr = this->reg.pop();
		const auto value = this->reg.pop();
		this->stack.write(addr.u, value);
	}
	void LtnVM::scrap() {
		this->reg.pop();
	}
	void LtnVM::makevar() {
		this->stack.makeVar();
	}
	void LtnVM::at() {
		const auto index = this->reg.pop();
		const auto indexable = this->reg.pop();
		if(indexable.type == Value::Type::ARRAY) {
			const auto & arr = heap.read<Array>(indexable.u);
			if(index.u >= arr.size()) {
				throw std::runtime_error{"Array out range"};
			}
			this->reg.push(arr[index.u]);
			return;
		}
		throw std::runtime_error{"Not an indexable type"};
	}
	void LtnVM::at_write() {
		const auto index = this->reg.pop();
		const auto indexable = this->reg.pop();
		const auto value = this->reg.pop();
		if(indexable.type == Value::Type::ARRAY) {
			auto & arr = heap.read<Array>(indexable.u);
			if(index.u >= arr.size()) {
				throw std::runtime_error{"Array out range"};
			}
			arr[index.u] = value;
			return;
		}
		throw std::runtime_error{"Not an indexable type"};
	}
}