#include "LtnVM.hxx"
#include "index.hxx"

namespace ltn::vm {
	namespace {
		void guardEmpty(const auto & collection) {
			if(collection.empty()) throw except::empty_collection();
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
		void removeI(const Value ref, Heap & heap, std::int64_t i, std::int64_t size = 1) {
			auto & collection = heap.read<Collection>(ref.u).get();
			guard_index(collection, i);
			const auto begin = collection.begin() + i;
			const auto end = begin + size;
			collection.erase(begin, end);
		}

		void removeM(const Value ref, Heap & heap, const Value key) {
			auto & map = heap.read<Map>(ref.u).get(); 
			map.erase(key);
		}
	}  

	void LtnVM::remove() {
		const auto type = this->fetch_byte();

		switch (type) {
		case 0: {
			const auto ref = this->core.reg.pop();
			if(is_string(ref)) return removeFirst<String>(ref, this->core.heap);
			if(is_array(ref)) return removeFirst<Array>(ref, this->core.heap);
			throw except::invalid_argument();
		} break;

		case 1: {
			const auto key = this->core.reg.pop();
			const auto ref = this->core.reg.pop();
			if(is_map(ref)) return removeM(ref, this->core.heap, key);
			const auto index = to_index(key);
			if(is_string(ref)) return removeI<String>(ref, this->core.heap, index);
			if(is_array(ref)) return removeI<Array>(ref, this->core.heap, index);
			throw except::invalid_argument();
		} break;

		case 2: {
			const auto ref = this->core.reg.pop();
			if(is_string(ref)) return removeLast<String>(ref, this->core.heap);
			if(is_array(ref)) return removeLast<Array>(ref, this->core.heap);
			throw except::invalid_argument();
		} break;

		default:
			throw except::invalid_argument();
			break;
		}
	}
}