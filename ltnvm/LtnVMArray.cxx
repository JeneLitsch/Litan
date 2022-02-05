#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "cast.hxx"
#include "index.hxx"

namespace ltn::vm {
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

		throw std::runtime_error{"Not an indexable type"};
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
			const auto & arr = this->heap.read<Array>(ref.u);
			this->reg.push(arr.arr.front());
		}
		else {
			throw std::runtime_error{"Cannot get front element from non array type"};
		}
	}

	
	void LtnVM::back() {
		const auto ref = this->reg.pop();
		if (isArr(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u);
			this->reg.push(arr.arr.back());
		}
		else {
			throw std::runtime_error{"Cannot get back element from non array type"};
		}
	}


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

		throw std::runtime_error{"Can only get iterator from Array or Range"};
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

		throw std::runtime_error{"Can only get iterator from Array or Range"};
	}
}