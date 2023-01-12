#pragma once
#include <map>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/compare.hxx"
namespace ltn::vm {
	class Heap;
	// Implements stack, queue, ...
	struct Comparator {
		Heap * heap;
		bool operator()(const Value l, const Value r) const {
			return compare(l, r, *heap) < 0;
		}
	};

	using Map = std::map<Value, Value, Comparator>;

	inline Map clone(const Map & map) {
		return map;
	}
}