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

		void destroy(std::uint64_t ptr);

		std::vector<std::uint64_t> & accessArray(std::uint64_t ptr);
		std::string & accessString(std::uint64_t ptr);
	private:
		std::map<std::uint64_t, HeapObject> objects;
		std::queue<std::uint64_t> resuseableIDs;
		std::uint64_t nextID;
	};
}
