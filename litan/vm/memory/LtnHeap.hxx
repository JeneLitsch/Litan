#pragma once 
#include <map>
#include <vector>
#include <cstdint>
#include <queue>
#include "LtnHeapObject.hxx"
namespace ltn {
	class Heap {
	public:
		Heap();
		void clear();

		std::uint64_t allocateArray();
		std::uint64_t allocateString();
		std::uint64_t copy(std::uint64_t ptr);

		void destroy(std::uint64_t ptr);

		std::vector<std::uint64_t> & accessArray(std::uint64_t ptr);
		std::string & accessString(std::uint64_t ptr);

		bool exists(std::uint64_t ptr) const;
	private:
		std::uint64_t createPtr();
		std::map<std::uint64_t, HeapObject> objects;
		std::queue<std::uint64_t> resuseableIDs;
		std::uint64_t nextID;
	};
}
