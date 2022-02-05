#include "LtnVM.hxx"
#include "index.hxx"
namespace ltn::vm {
	namespace {
		void guardEmpty(const auto & collection) {
			if(collection.empty()) {
				throw std::runtime_error{"Cannot remove from empty collection"};
			}
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
		void removeI(const Value ref, Heap & heap, std::int64_t index) {
			auto & collection = heap.read<Collection>(ref.u).get(); 
			if(index < 0) {
				throw std::runtime_error{"Negative idex is not allowed"};
			}
			if(collection.size() <= static_cast<std::size_t>(index)) {
				throw std::runtime_error{"Index out of range"};
			}
			collection.erase(collection.begin() + index);
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
			throw std::runtime_error{"Can only remove from a collection"};
		} break;

		case 1: {
			const auto key = this->reg.pop();
			const auto ref = this->reg.pop();
			if(isMap(ref)) return removeM(ref, this->heap, key);
			const auto index = toIndex(key);
			if(isStr(ref)) return removeI<String>(ref, this->heap, index);
			if(isArr(ref)) return removeI<Array>(ref, this->heap, index);
			throw std::runtime_error{"Can only remove from a collection"};
		} break;

		case 2: {
			const auto ref = this->reg.pop();
			if(isStr(ref)) return removeLast<String>(ref, this->heap);
			if(isArr(ref)) return removeLast<Array>(ref, this->heap);
			throw std::runtime_error{"Can only remove from a collection"};
		} break;

		default:
			throw std::runtime_error{"Invalid remove type"};
			break;
		}
	}
}