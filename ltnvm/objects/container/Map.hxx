#pragma once
#include <map>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/utils/compare.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	class Heap;
	// Implements stack, queue, ...
	struct Comparator {
		VMCore * core;
		bool operator()(const Value l, const Value r) const {
			return compare(l, r, *core) < 0;
		}
	};



	class Map : public Object {
	public:
		using std_map = std::map<Value, Value, Comparator>;
		using iterator = std_map::const_iterator;
		Map(VMCore * core) 
			: map{Comparator{core}} {}

		std::uint64_t size() const {
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
			if(!this->contains(key)) ++this->version;
			return this->map[key];
		} 

		void erase(const Value & key) {
			++this->version;
			this->map.erase(key);
		}

		std::uint64_t get_version() const {
			return this->version;
		}
		
		virtual Value get_member(std::uint64_t id) const override;
	private:
		std_map map;
		std::uint64_t version = 0;
	};



	inline Map clone(const Map & map) {
		return map;
	}
}