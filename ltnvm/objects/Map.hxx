#pragma once
#include <map>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/compare.hxx"
namespace ltn::vm {
	class Heap;
	// Implements stack, queue, ...
	struct Comparator {
		VmCore * core;
		bool operator()(const Value l, const Value r) const {
			return compare(l, r, *core) < 0;
		}
	};

	using Map = std::map<Value, Value, Comparator>;

	inline Map clone(const Map & map) {
		return map;
	}
}