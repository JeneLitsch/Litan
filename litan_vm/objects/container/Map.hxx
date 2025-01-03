#pragma once
#include <map>
#include <string_view>
#include <vector>
#include "litan_vm/Value.hxx"
#include "litan_vm/utils/compare.hxx"
#include "litan_vm/objects/Object.hxx"
#include "Array.hxx"

namespace ltn::vm {
	class Heap;
	// Implements stack, queue, ...
	struct Comparator {
		VMCore * core;
		bool operator()(const Value l, const Value r) const {
			return strict_compare(l, r, *core) < 0;
		}
	};



	class Map : public Object {
	public:
		using std_map = std::map<Value, Value, Comparator>;
		using iterator = std_map::const_iterator;
		Map(VMCore * core) 
			: map{Comparator{core}}
			, core{core} {}

		virtual Value get_member(VMCore & core, std::uint64_t id) const override;
		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;

		std::uint64_t size() const {
			return std::size(this->map);
		}

		bool empty() const {
			return this->size() == 0;
		}

		auto begin() const { return std::begin(this->map); }
		auto end() const { return std::end(this->map); }


		const Value & at(const Value & key) const  {
			if(contains(key)) {
				return this->map.at(key);
			}
			else {
				return value::null;
			}
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

		inline const std_map & get_underlying() const {
			return this->map;
		}

		inline std_map & get_underlying() {
			return this->map;
		}

		Array keys() const;
		Array values() const;

		Map merged(const Map & other) const;
	private:
		std_map map;
		std::uint64_t version = 0;
		VMCore * core;
	};



	inline Map clone(const Map & map) {
		return map;
	}
}