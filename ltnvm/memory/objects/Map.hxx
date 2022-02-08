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
		bool operator()(const Value l, const Value r) const;
	};
	struct Map {
		constexpr static std::string_view typeName = "map";
		
		std::map<Value, Value, Comparator> map;

		Map(Heap & heap) : map(Comparator{&heap}) {}
		
		const auto & get() const {
			return this->map;
		}
		
		auto & get() {
			return this->map;
		}

		auto clone() const {
			return *this;
		}
	};
}