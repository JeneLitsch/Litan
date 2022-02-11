#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>
#include <sstream>

namespace ltn::vm {
	void LtnVM::tRy() {
		const auto addr = this->fetchUint();
		const auto depth = this->stack.depth();
		const auto handler = ExceptHandler{addr, depth};
		this->exceptHandlers.push_back(handler);
	}

	void LtnVM::untry() {
		this->exceptHandlers.pop_back();
	}

	void LtnVM::state() {
		const auto regSize = this->reg.size();
		const auto stackSize = this->stack.size();
		const auto heapSize = this->heap.size();
		std::stringstream ss;
		ss << "register size: " << regSize << "\n";
		ss << "stack size: " << stackSize << "\n";
		ss << "heap size: " << heapSize << "\n";
		const auto refToString = this->heap.alloc<String>({ss.str()});
		this->reg.push(Value{refToString, Value::Type::STRING});
	}
}