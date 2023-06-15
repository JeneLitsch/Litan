#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	namespace {
		using array = Array;
		using string = std::string;



		void guardEmpty(const auto & collection) {
			if(collection.empty()) throw except::empty_collection();
		}

		

		template<typename Collection>
		Value remove_first(const Value ref, Heap & heap) {
			auto & collection = heap.read<Collection>(ref.u); 
			guardEmpty(collection);
			collection.erase(collection.begin());
			return value::null;
		}



		template<typename Collection>
		Value remove_last(const Value ref, Heap & heap) {
			auto & collection = heap.read<Collection>(ref.u); 
			guardEmpty(collection);
			collection.pop_back();
			return value::null;
		}



		template<typename Collection>
		Value remove_index(const Value ref, Heap & heap, const Value & index, std::int64_t size = 1) {
			auto & collection = heap.read<Collection>(ref.u);
			const auto i = to_index(index, std::size(collection));
			const auto begin = collection.begin() + i;
			const auto end = begin + size;
			collection.erase(begin, end);
			return value::null;
		}



		Value remove_m(const Value ref, Heap & heap, const Value key) {
			auto & map = heap.read<Map>(ref.u); 
			map.erase(key);
			return value::null;
		}
	}

	

	Value remove_front(VmCore & core) {
		const auto ref = core.stack.pop();
		if(is_string(ref)) return remove_first<String>(ref, core.heap);
		if(is_array(ref)) return remove_first<Array>(ref, core.heap);
		throw except::invalid_argument();
	}



	Value remove_back(VmCore & core) {
		const auto ref = core.stack.pop();
		if(is_string(ref)) return remove_last<String>(ref, core.heap);
		if(is_array(ref)) return remove_last<Array>(ref, core.heap);
		throw except::invalid_argument();
	}



	Value remove(VmCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		if(is_map(ref)) return remove_m(ref, core.heap, key);
		if(is_string(ref)) return remove_index<String>(ref, core.heap, key);
		if(is_array(ref)) return remove_index<Array>(ref, core.heap, key);
		throw except::invalid_argument();
	}
}