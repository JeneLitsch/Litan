#include "LtnVM.hxx"
#include <stdexcept>
#include "cast.hxx"
#include "index.hxx"
namespace ltn::vm {
	
	void LtnVM::push() {
		const auto elem = reg.pop();
		const auto ref = reg.pop();

		if(isArr(ref)) {
			auto & container = heap.read<Array>(ref.u).get();
			container.push_back(elem);
			return;
		}

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

		if(isArr(ref)) {
			auto & container = heap.read<Array>(ref.u).get();
			const auto elem = container.back();
			container.pop_back();
			this->reg.push(elem);
			return;
		}

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


	void LtnVM::at() {
		const auto key = this->reg.pop();
		const auto ref = this->reg.pop();
		
		if(isArr(ref)) {
			const auto & arr = heap.read<Array>(ref.u).get();
			const auto index = toIndex(key);
			guardIndex(arr, index);
			this->reg.push(arr[index]);
			return;
		}

		if(isStr(ref)) {
			const auto & str = heap.read<String>(ref.u).get();
			const auto index = toIndex(key);
			guardIndex(str, index);
			const auto chr = str[index];
			this->reg.push(value::character(chr));
			return;
		}

		if(isMap(ref)) {
			const auto & map = heap.read<Map>(ref.u).get();
			if(map.contains(key)) {
				this->reg.push(map.at(key));
			}
			else {
				this->reg.push(value::null);
			}
			return;
		}

		throw except::invalidArgument();
	}


	void LtnVM::size() {
		const auto ref = this->reg.pop();
		
		if (isArr(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u);
			this->reg.push(static_cast<std::int64_t>(arr.arr.size()));
			return;
		}

		if(isStr(ref)) {
			const auto & str = this->heap.read<String>(ref.u);
			this->reg.push(static_cast<std::int64_t>(str.str.size()));
			return;
		}

		if(isFxPtr(ref)) {
			const auto & fxPtr = this->heap.read<FxPointer>(ref.u);
			this->reg.push(static_cast<std::int64_t>(fxPtr.params));
			return;
		}
		
		if(isRange(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(range.end - range.begin);
			return;
		}

		if(isQueue(ref) || isStack(ref)) {
			const auto & deq = this->heap.read<Deque>(ref.u).get();
			this->reg.push(static_cast<std::int64_t>(deq.size()));
			return;
		}

		if(isMap(ref)) {
			const auto & map = this->heap.read<Map>(ref.u).get();
			this->reg.push(static_cast<std::int64_t>(map.size()));
			return;
		}

		this->reg.push(static_cast<std::int64_t>(0));
	}


	void LtnVM::front() {
		const auto ref = this->reg.pop();
		
		if (isArr(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u).get();
			this->reg.push(arr.front());
			return;
		}

		if (isStr(ref)) {
			const auto & str = this->heap.read<String>(ref.u).get();
			const auto chr = str.front(); 
			this->reg.push(value::character(chr));
			return;
		}

		throw except::invalidArgument();
	}

	
	void LtnVM::back() {
		const auto ref = this->reg.pop();
		
		if (isArr(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u).get();
			this->reg.push(arr.back());
			return;
		}

		if (isStr(ref)) {
			const auto & str = this->heap.read<String>(ref.u).get();
			const auto chr = str.back(); 
			this->reg.push(value::character(chr));
			return;
		}

		throw except::invalidArgument();
	}	
}