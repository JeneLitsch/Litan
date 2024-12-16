#include "algorithm.hxx"
#include "ltnvm/utils/compare.hxx"
#include "ltnvm/utils/run_function.hxx"
#include "ltnvm/Exception.hxx"
#include <algorithm>
#include <numeric>

namespace ltn::vm::build_in {
	static auto to_cpp_range(const Value ref) {
		if(is_array(ref)) {
			Array * array = value::as<Array>(ref);
			const auto begin = std::begin(*array);
			const auto end = std::end(*array);
			return std::make_pair(begin, end);
		}

		throw except::invalid_argument();
	}



	auto smaller(VMCore & core) {
		return [&core] (const Value l, const Value r) {
			return compare(l, r, core) < 0;
		};
	}



	auto bigger(VMCore & core) {
		return [&core] (const Value l, const Value r) {
			return compare(l, r, core) > 0;
		};
	}



	auto predicate(VMCore & core, const Value key) {
		return [&core, key] (const Value elem) {
			return compare(elem, key, core) == 0;
		};
	}




	// Algorithms
	Value sort_desc(VMCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref);
		const auto comp = bigger(core);
		std::sort(begin, end, comp);
		return value::null;
	}



	Value sort_ascn(VMCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref);
		const auto comp = smaller(core);
		std::sort(begin, end, comp);
		return value::null;
	}



	Value is_sorted_ascn(VMCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref);
		const auto comp = smaller(core);
		return value::boolean(std::is_sorted(begin, end, comp));
	}



	Value is_sorted_desc(VMCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref);
		const auto comp = bigger(core);
		return value::boolean(std::is_sorted(begin, end, comp));
	}



	Value find(VMCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref);
		const auto pred = predicate(core, key);
		const auto found = std::find_if(begin, end, pred);
		if(found == end) {
			return value::null;
		}
		else {
			const auto dist = std::distance(begin, found); 
			return value::integer(dist);
		}
	}


	
	Value fill(VMCore & core) {
		const auto value = core.stack.pop();
		const auto [begin, end] = to_cpp_range(core.stack.pop());
		std::fill(begin, end, value);
		return value::null;
	}



	Value reverse(VMCore & core) {
		const auto ref = core.stack.pop();
		const auto [begin, end] = to_cpp_range(ref);
		std::reverse(begin, end);
		return value::null;
	}



	namespace {
		Value reduce_l_impl(VMCore & core, const Value & function, Value value, Iterator & iter) {
			while(true) {
				auto elem = iter.next();
				if(is_iterator_stop(elem)) break;
				core.stack.push(value);
				value = run_function(core, function, value, elem);
				core.stack.pop();
			}

			return value;
		}
	}



	Value reduce_l_2(VMCore & core) {
		const auto function = core.stack.pop();
		const auto container = core.stack.pop();

		auto iter_ref = iterator::wrap(container, core);
		Iterator * iter = value::as<Iterator>(iter_ref);

		auto first = iter->next();
		if(is_iterator_stop(first)) return value::null;

		core.stack.push(function);
		core.stack.push(iter_ref);

		auto result = reduce_l_impl(core, function, first, *iter);

		core.stack.pop();
		core.stack.pop();

		return result;
	}



	Value reduce_l_3(VMCore & core) {
		auto init = core.stack.pop();
		const auto function = core.stack.pop();
		const auto container = core.stack.pop();
		auto iter_ref = iterator::wrap(container, core);
		Iterator * iter = value::as<Iterator>(iter_ref);

		core.stack.push(init);
		core.stack.push(iter_ref);
		core.stack.push(function);

		auto result = reduce_l_impl(core, function, init, *iter);

		core.stack.pop();
		core.stack.pop();
		core.stack.pop();

		return result;
	}
}