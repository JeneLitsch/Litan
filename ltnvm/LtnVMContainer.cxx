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
		
		throw std::runtime_error{"Can only push to container type"};
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
	
		throw std::runtime_error{"Can only pop from container type"};
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

		throw std::runtime_error{"Can only peek at container type"};
	}
}