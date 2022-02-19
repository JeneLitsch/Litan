#include "LtnVM.hxx"
#include "index.hxx"

namespace ltn::vm {
	namespace {
		void guardEmpty(const auto & collection) {
			if(collection.empty()) throw except::emptyCollection();
		}

		template<typename Collection>
		void removeLast(const Value ref, Heap & heap) {
			auto & collection = heap.read<Collection>(ref.u).get(); 
			guardEmpty(collection);
			collection.pop_back();
		}

		template<typename Collection>
		void removeFirst(const Value ref, Heap & heap) {
			auto & collection = heap.read<Collection>(ref.u).get(); 
			guardEmpty(collection);
			collection.erase(collection.begin());
		}

		template<typename Collection>
		void removeI(const Value ref, Heap & heap, std::int64_t index, std::int64_t size = 1) {
			auto & collection = heap.read<Collection>(ref.u).get(); 
			if(index < 0) {
				throw except::negativeIndex();
			}
			if(collection.size() <= static_cast<std::size_t>(index)) {
				throw except::outOfRange();
			}
			const auto begin = collection.begin() + index;
			const auto end = begin + size;
			collection.erase(begin, end);
		}

		void removeM(const Value ref, Heap & heap, const Value key) {
			auto & map = heap.read<Map>(ref.u).get(); 
			map.erase(key);
		}
	}  

	void LtnVM::remove() {
		const auto type = this->fetchByte();

		switch (type) {
		case 0: {
			const auto ref = this->reg.pop();
			if(isStr(ref)) return removeFirst<String>(ref, this->heap);
			if(isArr(ref)) return removeFirst<Array>(ref, this->heap);
			throw except::invalidArgument();
		} break;

		case 1: {
			const auto key = this->reg.pop();
			const auto ref = this->reg.pop();
			if(isMap(ref)) return removeM(ref, this->heap, key);
			const auto index = toIndex(key);
			if(isStr(ref)) return removeI<String>(ref, this->heap, index);
			if(isArr(ref)) return removeI<Array>(ref, this->heap, index);
			throw except::invalidArgument();
		} break;

		case 2: {
			const auto ref = this->reg.pop();
			if(isStr(ref)) return removeLast<String>(ref, this->heap);
			if(isArr(ref)) return removeLast<Array>(ref, this->heap);
			throw except::invalidArgument();
		} break;

		default:
			throw except::invalidArgument();
			break;
		}
	}
}