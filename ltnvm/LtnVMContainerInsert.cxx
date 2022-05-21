#include "LtnVM.hxx"
#include "index.hxx"
#include "convert.hxx"

namespace ltn::vm {
	namespace {
		using array = std::vector<Value>;
		using string = std::string;

		// Front insertions
		void push_f(array & arr, Heap &, const Value elem) {
			arr.insert(arr.begin(), elem);
		}

		void push_f(string & str, Heap & heap, const Value elem) {
			const auto strL = convert::to_string(elem, heap);
			str = strL + str;
		}

		template<typename Collection>
		void push_f(const Value ref, Heap & heap, const Value elem) {
			auto & collection = heap.read<Collection>(ref.u).get();
			return push_f(collection, heap, elem);
		}

		void insert_front(Register & reg, Heap & heap) {
			const auto elem = reg.pop();
			const auto ref = reg.pop();
			if(is_string(ref)) return push_f<String>(ref, heap, elem);
			if(is_array(ref)) return push_f<Array>(ref, heap, elem);
			throw except::invalid_argument();
		}


		// Back insertsion
		void push_b(array & arr, Heap &, const Value elem) {
			arr.push_back(elem);
		}

		void push_b(string & str, Heap & heap, const Value elem) {
			const auto & strR = convert::to_string(elem, heap);
			str += strR;
		}

		template<typename Collection>
		void push_b(const Value ref, Heap & heap, const Value elem) {
			auto & collection = heap.read<Collection>(ref.u).get();
			push_b(collection, heap, elem);
		}

		void insert_back(Register & reg, Heap & heap) {
			const auto elem = reg.pop();
			const auto ref = reg.pop();
			if(is_string(ref)) return push_b<String>(ref, heap, elem);
			if(is_array(ref)) return push_b<Array>(ref, heap, elem);
			throw except::invalid_argument();
		}

		// Map insertion		
		void push_m(const Value ref, Heap & heap, const Value elem, const Value key) {
			auto & map = heap.read<Map>(ref.u).get();
			map[key] = elem;
		}

		// Index insertion
		void push_i(array & arr, Heap &, const Value elem, auto i) {
			arr.insert(arr.begin() + i, elem);
		}

		void push_i(string & str, Heap & heap, const Value elem, auto i) {
			const auto & strX = convert::to_string(elem, heap);
			const auto begin = std::begin(strX);
			const auto end = std::end(strX);
			const auto at = std::begin(str) + i;
			str.insert(at, begin, end);
		}

		template<typename Collection>
		void push_i(const Value ref, Heap & heap, const Value elem, auto i) {
			auto & collection = heap.read<Collection>(ref.u).get(); 
			if(i != static_cast<std::int64_t>(collection.size())) {
				guard_index(collection, i);
			}
			push_i(collection, heap, elem, i);
		}

		void insertIndex(Register & reg, Heap & heap) {
			const auto elem = reg.pop();
			const auto key = reg.pop();
			const auto ref = reg.pop();
			if(is_map(ref)) return push_m(ref, heap, elem, key);
			const auto index = to_index(key);
			if(is_string(ref)) return push_i<String>(ref, heap, elem, index);
			if(is_array(ref)) return push_i<Array>(ref, heap, elem, index);
			throw except::invalid_argument();
		}
	}
	

	void LtnVM::insert() {
		const auto type = this->fetch_byte();
		switch (type) {
		case 0: return insert_front(this->core.reg, this->core.heap); 
		case 1: return insertIndex( this->core.reg, this->core.heap);
		case 2: return insert_back( this->core.reg, this->core.heap);
		default: throw except::invalid_argument();
		}
	}

	void LtnVM::at_write() {
		const auto key = this->core.reg.pop();
		const auto ref = this->core.reg.pop();
		const auto elem = this->core.reg.pop();
		
		if(is_array(ref)) {
			auto & arr = this->core.heap.read<Array>(ref.u).get();
			const auto index = to_index(key);
			guard_index(arr, index);
			arr[static_cast<std::size_t>(index)] = elem;
			return;
		}

		if(is_string(ref)) {
			auto & str = this->core.heap.read<String>(ref.u).get();
			const auto index = to_index(key);
			guard_index(str, index);
			str[static_cast<std::size_t>(index)] = convert::to_char(elem);
			return;
		}

		if(is_map(ref)) {
			push_m(ref, this->core.heap, elem, key);
			return;
		}

		throw except::invalid_argument();
	}
}