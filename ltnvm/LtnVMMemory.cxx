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
			if(index.u >= arr.arr.size()) {
				throw std::runtime_error{"Array out range"};
			}
			this->reg.push(arr.arr[index.u]);
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
			if(index.u >= arr.arr.size()) {
				throw std::runtime_error{"Array out range"};
			}
			arr.arr[index.u] = value;
			return;
		}
		throw std::runtime_error{"Not an indexable type"};
	}

	void LtnVM::read_0() { this->reg.push(this->stack.read(0)); }
	void LtnVM::read_1() { this->reg.push(this->stack.read(1)); }
	void LtnVM::read_2() { this->reg.push(this->stack.read(2)); }
	void LtnVM::read_3() { this->reg.push(this->stack.read(3)); }

	void LtnVM::write_0() { this->stack.write(0, this->reg.pop()); }
	void LtnVM::write_1() { this->stack.write(1, this->reg.pop()); }
	void LtnVM::write_2() { this->stack.write(2, this->reg.pop()); }
	void LtnVM::write_3() { this->stack.write(3, this->reg.pop()); }
}