#include "LtnVM.hxx"
#include "index.hxx"
#include "cast.hxx"

namespace ltn::vm {
	namespace {
		using array = std::vector<Value>;
		using string = std::string;

		// Front insertions
		void pushF(array & arr, Heap &, const Value elem) {
			arr.insert(arr.begin(), elem);
		}

		void pushF(string & str, Heap & heap, const Value elem) {
			const auto strL = cast::to_string(elem, heap);
			str = strL + str;
		}

		template<typename Collection>
		void pushF(const Value ref, Heap & heap, const Value elem) {
			auto & collection = heap.read<Collection>(ref.u).get();
			return pushF(collection, heap, elem);
		}

		void insertFront(Register & reg, Heap & heap) {
			const auto elem = reg.pop();
			const auto ref = reg.pop();
			if(isStr(ref)) return pushF<String>(ref, heap, elem);
			if(isArr(ref)) return pushF<Array>(ref, heap, elem);
			throw except::invalidArgument();
		}


		// Back insertsion
		void pushB(array & arr, Heap &, const Value elem) {
			arr.push_back(elem);
		}

		void pushB(string & str, Heap & heap, const Value elem) {
			const auto & strR = cast::to_string(elem, heap);
			str += strR;
		}

		template<typename Collection>
		void pushB(const Value ref, Heap & heap, const Value elem) {
			auto & collection = heap.read<Collection>(ref.u).get();
			pushB(collection, heap, elem);
		}

		void insertBack(Register & reg, Heap & heap) {
			const auto elem = reg.pop();
			const auto ref = reg.pop();
			if(isStr(ref)) return pushB<String>(ref, heap, elem);
			if(isArr(ref)) return pushB<Array>(ref, heap, elem);
			throw except::invalidArgument();
		}

		// Map insertion		
		void pushM(const Value ref, Heap & heap, const Value elem, const Value key) {
			auto & map = heap.read<Map>(ref.u).get();
			map[key] = elem;
		}

		// Index insertion
		void pushI(array & arr, Heap &, const Value elem, auto i) {
			arr.insert(arr.begin() + i, elem);
		}

		void pushI(string & str, Heap & heap, const Value elem, auto i) {
			const auto & strX = cast::to_string(elem, heap);
			const auto begin = std::begin(strX);
			const auto end = std::end(strX);
			const auto at = std::begin(str) + i;
			str.insert(at, begin, end);
		}

		template<typename Collection>
		void pushI(const Value ref, Heap & heap, const Value elem, auto i) {
			auto & collection = heap.read<Collection>(ref.u).get(); 
			if(i != static_cast<std::int64_t>(collection.size())) {
				guardIndex(collection, i);
			}
			pushI(collection, heap, elem, i);
		}

		void insertIndex(Register & reg, Heap & heap) {
			const auto elem = reg.pop();
			const auto key = reg.pop();
			const auto ref = reg.pop();
			if(isMap(ref)) return pushM(ref, heap, elem, key);
			const auto index = toIndex(key);
			if(isStr(ref)) return pushI<String>(ref, heap, elem, index);
			if(isArr(ref)) return pushI<Array>(ref, heap, elem, index);
			throw except::invalidArgument();
		}
	}
	

	void LtnVM::insert() {
		const auto type = this->fetchByte();
		switch (type) {
		case 0: return insertFront(reg, heap); 
		case 1: return insertIndex(reg, heap);
		case 2: return insertBack(reg, heap);
		default: throw except::invalidArgument();
		}
	}

	void LtnVM::at_write() {
		const auto key = this->reg.pop();
		const auto ref = this->reg.pop();
		const auto elem = this->reg.pop();
		
		if(isArr(ref)) {
			auto & arr = heap.read<Array>(ref.u).get();
			const auto index = toIndex(key);
			guardIndex(arr, index);
			arr[index] = elem;
			return;
		}

		if(isStr(ref)) {
			auto & str = heap.read<String>(ref.u).get();
			const auto index = toIndex(key);
			guardIndex(str, index);
			str[index] = cast::to_char(elem);
			return;
		}

		if(isMap(ref)) {
			pushM(ref, this->heap, elem, key);
			return;
		}

		throw except::invalidArgument();
	}
}