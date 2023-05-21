#include "algorithm.hxx"
#include "ltnvm/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/stringify.hxx"

namespace ltn::vm::build_in {
	namespace {
		using array = Array;
		using string = std::string;

		Value push_f(array & arr, Heap &, const Value elem) {
			arr.insert(arr.begin(), elem);
			return value::null;
		}



		Value push_f(string & str, Heap & heap, const Value elem) {
			const auto strL = stringify(elem, heap);
			str = strL + str;
			return value::null;
		}



		template<typename Collection>
		Value push_f(const Value ref, Heap & heap, const Value elem) {
			auto & collection = heap.read<Collection>(ref.u);
			return push_f(collection, heap, elem);
		}
	}



	Value insert_front(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_string(ref)) return push_f<String>(ref, core.heap, elem);
		if(is_array(ref)) return push_f<Array>(ref, core.heap, elem);
		throw except::invalid_argument();
	}



	namespace {
		Value push_b(array & arr, Heap &, const Value elem) {
			arr.push_back(elem);
			return value::null;
		}



		Value push_b(string & str, Heap & heap, const Value elem) {
			const auto strR = stringify(elem, heap);
			str += strR;
			return value::null;
		}



		template<typename Collection>
		Value push_b(const Value ref, Heap & heap, const Value elem) {
			auto & collection = heap.read<Collection>(ref.u);
			return push_b(collection, heap, elem);
		}
	}



	Value insert_back(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_string(ref)) return push_b<String>(ref, core.heap, elem);
		if(is_array(ref)) return push_b<Array>(ref, core.heap, elem);
		throw except::invalid_argument();
	}



	namespace {
		Value push_m(const Value ref, Heap & heap, const Value elem, const Value key) {
			auto & map = heap.read<Map>(ref.u);
			map[key] = elem;
			return value::null;
		}



		Value push_i(array & arr, Heap &, const Value elem, auto i) {
			arr.insert(arr.begin() + i, elem);
			return value::null;
		}



		Value push_i(string & str, Heap & heap, const Value elem, auto i) {
			const auto strX = stringify(elem, heap);
			const auto begin = std::begin(strX);
			const auto end = std::end(strX);
			const auto at = std::begin(str) + i;
			str.insert(at, begin, end);
			return value::null;
		}



		template<typename Collection>
		Value push_i(const Value ref, Heap & heap, const Value elem, auto i) {
			auto & collection = heap.read<Collection>(ref.u); 
			if(i != static_cast<std::int64_t>(collection.size())) {
				guard_index(collection, i);
			}
			return push_i(collection, heap, elem, i);
		}
	}



	Value insert(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_map(ref)) return push_m(ref, core.heap, elem, key);
		const auto index = to_index(key);
		if(is_string(ref)) return push_i<String>(ref, core.heap, elem, index);
		if(is_array(ref)) return push_i<Array>(ref, core.heap, elem, index);
		throw except::invalid_argument();
	}
}