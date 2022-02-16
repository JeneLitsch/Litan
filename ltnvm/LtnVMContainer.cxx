#include "LtnVM.hxx"
#include <stdexcept>
namespace ltn::vm {
	
	void LtnVM::push() {
		const auto elem = reg.pop();
		const auto ref = reg.pop();
		
		if(isStack(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			container.push_back(elem);
			return;
		}

		if(isQueue(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			container.push_back(elem);
			return;
		}
		
		throw except::invalidArgument();
	}

	void LtnVM::pop() {
		const auto ref = reg.pop();

		if(isStack(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			const auto elem = container.back();
			container.pop_back();
			this->reg.push(elem);
			return;
		}

		if(isQueue(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			const auto elem = container.front();
			container.pop_front();
			this->reg.push(elem);
			return;
		}
	
		throw except::invalidArgument();
	}

	void LtnVM::peek() {
		const auto ref = reg.pop();

		if(isStack(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			const auto elem = container.back();
			this->reg.push(elem);
			return;
		}

		if(isQueue(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			const auto elem = container.front();
			this->reg.push(elem);
			return;
		}

		throw except::invalidArgument();
	}


	void LtnVM::contains() {
		const auto key = reg.pop();
		const auto ref = reg.pop();

		if(isMap(ref)) {
			auto & container = heap.read<Map>(ref.u).get();
			this->reg.push(container.contains(key));
			return;
		}

		throw except::invalidArgument();
	}
}