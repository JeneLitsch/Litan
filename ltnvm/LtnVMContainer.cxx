#include "LtnVM.hxx"
#include <stdexcept>
#include "convert.hxx"
#include "index.hxx"
namespace ltn::vm {
	
	void LtnVM::push() {
		const auto elem = this->core.reg.pop();
		const auto ref = this->core.reg.pop();

		if(is_array(ref)) {
			auto & container = this->core.heap.read<Array>(ref.u).get();
			container.push_back(elem);
			return;
		}

		if(is_stack(ref)) {
			auto & container = this->core.heap.read<Deque>(ref.u).get();
			container.push_back(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = this->core.heap.read<Deque>(ref.u).get();
			container.push_back(elem);
			return;
		}
		
		throw except::invalid_argument();
	}


	void LtnVM::pop() {
		const auto ref = this->core.reg.pop();

		if(is_array(ref)) {
			auto & container = this->core.heap.read<Array>(ref.u).get();
			const auto elem = container.back();
			container.pop_back();
			this->core.reg.push(elem);
			return;
		}

		if(is_stack(ref)) {
			auto & container = this->core.heap.read<Deque>(ref.u).get();
			const auto elem = container.back();
			container.pop_back();
			this->core.reg.push(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = this->core.heap.read<Deque>(ref.u).get();
			const auto elem = container.front();
			container.pop_front();
			this->core.reg.push(elem);
			return;
		}
	
		throw except::invalid_argument();
	}


	void LtnVM::peek() {
		const auto ref = this->core.reg.pop();

		if(is_stack(ref)) {
			auto & container = this->core.heap.read<Deque>(ref.u).get();
			const auto elem = container.back();
			this->core.reg.push(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = this->core.heap.read<Deque>(ref.u).get();
			const auto elem = container.front();
			this->core.reg.push(elem);
			return;
		}

		throw except::invalid_argument();
	}


	void LtnVM::contains() {
		const auto key = this->core.reg.pop();
		const auto ref = this->core.reg.pop();

		if(is_map(ref)) {
			auto & container = this->core.heap.read<Map>(ref.u).get();
			this->core.reg.push(container.contains(key));
			return;
		}

		throw except::invalid_argument();
	}


	void LtnVM::at() {
		const auto key = this->core.reg.pop();
		const auto ref = this->core.reg.pop();
		
		if(is_array(ref)) {
			const auto & arr = this->core.heap.read<Array>(ref.u).get();
			const auto index = to_index(key);
			guard_index(arr, index);
			this->core.reg.push(arr[static_cast<std::size_t>(index)]);
			return;
		}

		if(is_range(ref)) {
			const auto & range = this->core.heap.read<Range>(ref.u);
			const auto & array = this->core.heap.read<Array>(range.array).get();
			const auto index = to_index(key);
			if(index < 0 || index >= range.end - range.begin) {
				throw except::out_of_range();
			} 
			this->core.reg.push(array[static_cast<std::size_t>(range.begin + index)]);
			return;
		}

		if(is_string(ref)) {
			const auto & str = this->core.heap.read<String>(ref.u).get();
			const auto index = to_index(key);
			guard_index(str, index);
			const auto chr = str[static_cast<std::size_t>(index)];
			this->core.reg.push(value::character(chr));
			return;
		}

		if(is_map(ref)) {
			const auto & map = this->core.heap.read<Map>(ref.u).get();
			if(map.contains(key)) {
				this->core.reg.push(map.at(key));
			}
			else {
				this->core.reg.push(value::null);
			}
			return;
		}

		throw except::invalid_argument();
	}


	void LtnVM::size() {
		const auto ref = this->core.reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = this->core.heap.read<Array>(ref.u);
			this->core.reg.push(static_cast<std::int64_t>(arr.arr.size()));
			return;
		}

		if(is_string(ref)) {
			const auto & str = this->core.heap.read<String>(ref.u);
			this->core.reg.push(static_cast<std::int64_t>(str.str.size()));
			return;
		}

		if(is_fxptr(ref)) {
			const auto & fxptr = this->core.heap.read<FxPointer>(ref.u);
			this->core.reg.push(static_cast<std::int64_t>(fxptr.params));
			return;
		}
		
		if(is_range(ref)) {
			const auto & range = this->core.heap.read<Range>(ref.u);
			this->core.reg.push(range.end - range.begin);
			return;
		}

		if(is_queue(ref) || is_stack(ref)) {
			const auto & deq = this->core.heap.read<Deque>(ref.u).get();
			this->core.reg.push(static_cast<std::int64_t>(deq.size()));
			return;
		}

		if(is_map(ref)) {
			const auto & map = this->core.heap.read<Map>(ref.u).get();
			this->core.reg.push(static_cast<std::int64_t>(map.size()));
			return;
		}

		this->core.reg.push(static_cast<std::int64_t>(0));
	}


	void LtnVM::front() {
		const auto ref = this->core.reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = this->core.heap.read<Array>(ref.u).get();
			this->core.reg.push(arr.front());
			return;
		}

		if (is_string(ref)) {
			const auto & str = this->core.heap.read<String>(ref.u).get();
			const auto chr = str.front(); 
			this->core.reg.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}

	
	void LtnVM::back() {
		const auto ref = this->core.reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = this->core.heap.read<Array>(ref.u).get();
			this->core.reg.push(arr.back());
			return;
		}

		if (is_string(ref)) {
			const auto & str = this->core.heap.read<String>(ref.u).get();
			const auto chr = str.back(); 
			this->core.reg.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}	
}