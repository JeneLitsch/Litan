#pragma once 
#include <map>
#include <vector>
#include <cstdint>
#include <queue>
#include "LtnvmHeapObject.hxx"
#include "LtnvmNullptrViolation.hxx"
#include "LtnvmPointerAccessViolation.hxx"
namespace ltn::vm {
	class Heap {
	public:
		Heap();
		void clear();

		std::uint64_t allocate(HeapType type);
		std::uint64_t allocate(std::size_t size = 0);

		std::uint64_t copy(std::uint64_t ptr);

		void destroy(std::uint64_t ptr);

		template <class T>
		T & access(std::uint64_t ptr) {
			if(ptr == 0) {
				throw NullptrViolation();
			}
			if(!this->objects.contains(ptr)) {
				throw PointerAccessViolation(ptr, "HeapObject");
			}
			return std::get<T>(this->objects.at(ptr).data);
		}

		HeapObject & access(std::uint64_t ptr) {
			return this->objects.at(ptr);
		}

		bool exists(std::uint64_t ptr) const;
	private:
		std::uint64_t createPtr();
		std::map<std::uint64_t, HeapObject> objects;
		std::queue<std::uint64_t> resuseableIDs;
		std::uint64_t nextID;
	};
}
