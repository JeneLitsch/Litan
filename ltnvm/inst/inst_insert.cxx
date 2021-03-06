#include "instructions.hxx"
#include "ltnvm/index.hxx"
#include "ltnvm/convert.hxx"

namespace ltn::vm::inst {
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

		void insert_index(Register & reg, Heap & heap) {
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
	

	void insert(VmCore & core) {
		const auto type = core.fetch_byte();
		switch (type) {
		case 0: return insert_front(core.reg, core.heap); 
		case 1: return insert_index( core.reg, core.heap);
		case 2: return insert_back( core.reg, core.heap);
		default: throw except::invalid_argument();
		}
	}
}