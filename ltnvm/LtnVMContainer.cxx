#include "LtnVM.hxx"
#include <stdexcept>
#include "convert.hxx"
#include "index.hxx"
namespace ltn::vm {
	
	void LtnVM::push() {
		const auto elem = reg.pop();
		const auto ref = reg.pop();

		if(is_array(ref)) {
			auto & container = heap.read<Array>(ref.u).get();
			container.push_back(elem);
			return;
		}

		if(is_stack(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			container.push_back(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			container.push_back(elem);
			return;
		}
		
		throw except::invalid_argument();
	}


	void LtnVM::pop() {
		const auto ref = reg.pop();

		if(is_array(ref)) {
			auto & container = heap.read<Array>(ref.u).get();
			const auto elem = container.back();
			container.pop_back();
			this->reg.push(elem);
			return;
		}

		if(is_stack(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			const auto elem = container.back();
			container.pop_back();
			this->reg.push(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			const auto elem = container.front();
			container.pop_front();
			this->reg.push(elem);
			return;
		}
	
		throw except::invalid_argument();
	}


	void LtnVM::peek() {
		const auto ref = reg.pop();

		if(is_stack(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			const auto elem = container.back();
			this->reg.push(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = heap.read<Deque>(ref.u).get();
			const auto elem = container.front();
			this->reg.push(elem);
			return;
		}

		throw except::invalid_argument();
	}


	void LtnVM::contains() {
		const auto key = reg.pop();
		const auto ref = reg.pop();

		if(is_map(ref)) {
			auto & container = heap.read<Map>(ref.u).get();
			this->reg.push(container.contains(key));
			return;
		}

		throw except::invalid_argument();
	}


	void LtnVM::at() {
		const auto key = this->reg.pop();
		const auto ref = this->reg.pop();
		
		if(is_array(ref)) {
			const auto & arr = heap.read<Array>(ref.u).get();
			const auto index = to_index(key);
			guard_index(arr, index);
			this->reg.push(arr[index]);
			return;
		}

		if(is_range(ref)) {
			const auto & range = heap.read<Range>(ref.u);
			const auto & array = heap.read<Array>(range.array).get();
			const auto index = to_index(key);
			if(index < 0 || index >= range.end - range.begin) {
				throw except::out_of_range();
			} 
			this->reg.push(array[range.begin + index]);
			return;
		}

		if(is_string(ref)) {
			const auto & str = heap.read<String>(ref.u).get();
			const auto index = to_index(key);
			guard_index(str, index);
			const auto chr = str[index];
			this->reg.push(value::character(chr));
			return;
		}

		if(is_map(ref)) {
			const auto & map = heap.read<Map>(ref.u).get();
			if(map.contains(key)) {
				this->reg.push(map.at(key));
			}
			else {
				this->reg.push(value::null);
			}
			return;
		}

		throw except::invalid_argument();
	}


	void LtnVM::size() {
		const auto ref = this->reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u);
			this->reg.push(static_cast<std::int64_t>(arr.arr.size()));
			return;
		}

		if(is_string(ref)) {
			const auto & str = this->heap.read<String>(ref.u);
			this->reg.push(static_cast<std::int64_t>(str.str.size()));
			return;
		}

		if(is_fxptr(ref)) {
			const auto & fxptr = this->heap.read<FxPointer>(ref.u);
			this->reg.push(static_cast<std::int64_t>(fxptr.params));
			return;
		}
		
		if(is_range(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(range.end - range.begin);
			return;
		}

		if(is_queue(ref) || is_stack(ref)) {
			const auto & deq = this->heap.read<Deque>(ref.u).get();
			this->reg.push(static_cast<std::int64_t>(deq.size()));
			return;
		}

		if(is_map(ref)) {
			const auto & map = this->heap.read<Map>(ref.u).get();
			this->reg.push(static_cast<std::int64_t>(map.size()));
			return;
		}

		this->reg.push(static_cast<std::int64_t>(0));
	}


	void LtnVM::front() {
		const auto ref = this->reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u).get();
			this->reg.push(arr.front());
			return;
		}

		if (is_string(ref)) {
			const auto & str = this->heap.read<String>(ref.u).get();
			const auto chr = str.front(); 
			this->reg.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}

	
	void LtnVM::back() {
		const auto ref = this->reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u).get();
			this->reg.push(arr.back());
			return;
		}

		if (is_string(ref)) {
			const auto & str = this->heap.read<String>(ref.u).get();
			const auto chr = str.back(); 
			this->reg.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}	
}