#pragma once
#include <map>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/utils/compare.hxx"
namespace ltn::vm {
	class Heap;
	// Implements stack, queue, ...
	struct Comparator {
		VmCore * core;
		bool operator()(const Value l, const Value r) const {
			return compare(l, r, *core) < 0;
		}
	};



	class Map {
	public:
		Map(VmCore * core) 
			: map{Comparator{core}} {}

		std::size_t size() const {
			return std::size(this->map);
		}

		bool empty() const {
			return this->size() == 0;
		}

		auto begin() const { return std::begin(this->map); }
		auto end() const { return std::end(this->map); }


		const Value & at(const Value & key) const  {
			return this->map.at(key);
		} 

		bool contains(const Value & key) const {
			return this->map.contains(key);
		}

		Value & operator[](const Value & key) {
			return this->map[key];
		} 

		void erase(const Value & key) {
			this->map.erase(key);
		}
	private:
		std::map<Value, Value, Comparator> map;
	};



	inline Map clone(const Map & map) {
		return map;
	}
}