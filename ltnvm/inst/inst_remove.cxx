#include "instructions.hxx"
#include "ltnvm/index.hxx"

namespace ltn::vm::inst {
	namespace {
		void guardEmpty(const auto & collection) {
			if(collection.empty()) throw except::empty_collection();
		}



		template<typename Collection>
		void remove_last(const Value ref, Heap & heap) {
			auto & collection = heap.read<Collection>(ref).get(); 
			guardEmpty(collection);
			collection.pop_back();
		}



		template<typename Collection>
		void remove_first(const Value ref, Heap & heap) {
			auto & collection = heap.read<Collection>(ref).get(); 
			guardEmpty(collection);
			collection.erase(collection.begin());
		}



		template<typename Collection>
		void remove_index(const Value ref, Heap & heap, std::int64_t i, std::int64_t size = 1) {
			auto & collection = heap.read<Collection>(ref).get();
			guard_index(collection, i);
			const auto begin = collection.begin() + i;
			const auto end = begin + size;
			collection.erase(begin, end);
		}



		void remove_m(const Value ref, Heap & heap, const Value key) {
			auto & map = heap.read<Map>(ref); 
			map.map.erase(key);
		}
	}  



	void remove(VmCore & core) {
		const auto type = core.fetch_byte();

		switch (type) {
		case 0: {
			const auto ref = core.stack.pop();
			if(is_string(ref)) return remove_first<String>(ref, core.heap);
			if(is_array(ref)) return remove_first<Array>(ref, core.heap);
			throw except::invalid_argument();
		} break;

		case 1: {
			const auto key = core.stack.pop();
			const auto ref = core.stack.pop();
			if(is_map(ref)) return remove_m(ref, core.heap, key);
			const auto index = to_index(key);
			if(is_string(ref)) return remove_index<String>(ref, core.heap, index);
			if(is_array(ref)) return remove_index<Array>(ref, core.heap, index);
			throw except::invalid_argument();
		} break;

		case 2: {
			const auto ref = core.stack.pop();
			if(is_string(ref)) return remove_last<String>(ref, core.heap);
			if(is_array(ref)) return remove_last<Array>(ref, core.heap);
			throw except::invalid_argument();
		} break;

		default:
			throw except::invalid_argument();
			break;
		}
	}
}