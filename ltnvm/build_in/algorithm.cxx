#include "algorithm.hxx"
#include "ltnvm/compare.hxx"
#include "ltnvm/Exception.hxx"
#include <algorithm>
#include <numeric>

namespace ltn::vm::build_in {
	static auto to_cpp_range(const Value ref, Heap & heap) {
		if(is_array(ref)) {
			auto & array = heap.read<Array>(ref).get();
			const auto begin = array.begin();
			const auto end = array.end();
			return std::make_pair(begin, end);
		}

		throw except::invalid_argument();
	}



	auto smaller(Heap & heap) {
		return [&heap] (const Value l, const Value r) {
			return compare(l, r, heap) < 0;
		};
	}



	auto bigger(Heap & heap) {
		return [&heap] (const Value l, const Value r) {
			return compare(l, r, heap) > 0;
		};
	}



	auto predicate(Heap & heap, const Value key) {
		return [&heap, key] (const Value elem) {
			return compare(elem, key, heap) == 0;
		};
	}




	// Algorithms
	Value sort_desc(VmCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref, core.heap);
		const auto comp = bigger(core.heap);
		std::sort(begin, end, comp);
		return value::null;
	}



	Value sort_ascn(VmCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref, core.heap);
		const auto comp = smaller(core.heap);
		std::sort(begin, end, comp);
		return value::null;
	}



	Value is_sorted_ascn(VmCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref, core.heap);
		const auto comp = smaller(core.heap);
		return std::is_sorted(begin, end, comp);
	}



	Value is_sorted_desc(VmCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref, core.heap);
		const auto comp = bigger(core.heap);
		return std::is_sorted(begin, end, comp);
	}



	Value find(VmCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref, core.heap);
		const auto pred = predicate(core.heap, key);
		const auto found = std::find_if(begin, end, pred);
		if(found == end) {
			return value::null;
		}
		else {
			const auto dist = std::distance(begin, found); 
			return value::integer(dist);
		}
	}


	
	Value fill(VmCore & core) {
		const auto value = core.stack.pop();
		const auto [begin, end] = to_cpp_range(core.stack.pop(), core.heap);
		std::fill(begin, end, value);
		return value::null;
	}



	Value reverse(VmCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref, core.heap);
		std::reverse(begin, end);
		return value::null;
	}
}