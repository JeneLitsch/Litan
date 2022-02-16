#include "LtnVM.hxx"
#include "index.hxx"
#include "cast.hxx"

namespace ltn::vm {
	namespace {
		template<typename Collection>
		void insertFront(const Value ref, Heap & heap, const Value elem) {
			auto & collection = heap.read<Collection>(ref.u).get(); 

			if constexpr(std::same_as<Collection, String>) {
				collection = cast::to_string(elem, heap) + collection;
				return;
			}

			else if constexpr(std::same_as<Collection, Array>) {
				collection.insert(collection.begin(), elem);
				return;
			}

			else {
				static_assert("Only for String and Array");
			}
		}


		template<typename Collection>
		void insertBack(const Value ref, Heap & heap, const Value elem) {
			auto & collection = heap.read<Collection>(ref.u).get(); 

			if constexpr(std::same_as<Collection, String>) {
				const auto & str = cast::to_string(elem, heap);
				collection += str;
				return;
			}

			else if constexpr(std::same_as<Collection, Array>) {
				collection.push_back(elem);
				return;
			}

			else {
				static_assert("Only for String and Array");
			}
		}


		template<typename Collection>
		void insertI(const Value ref, Heap & heap, const Value elem, std::int64_t i) {
			auto & collection = heap.read<Collection>(ref.u).get(); 
			guardIndex(collection, i);

			if constexpr(std::same_as<Collection, String>) {
				const auto & str = cast::to_string(elem, heap);
				collection.insert(static_cast<std::size_t>(i), str);
				return;
			}

			else if constexpr(std::same_as<Collection, Array>) {
				collection.insert(collection.begin() + i, elem);
				return;
			}

			else {
				static_assert("Only for String and Array");
			}
		}

		void insertM(const Value ref, Heap & heap, const Value key, const Value elem) {
			auto & map = heap.read<Map>(ref.u).get();
			map[key] = elem;
		}
	}

	void LtnVM::insert() {
		const auto type = this->fetchByte();

		switch (type) {
		case 0: {
			const auto elem = this->reg.pop();
			const auto ref = this->reg.pop();
			if(isStr(ref)) return insertFront<String>(ref, this->heap, elem);
			if(isArr(ref)) return insertFront<Array>(ref, this->heap, elem);
			throw except::invalidArgument();
		} break;

		case 1: {
			const auto elem = this->reg.pop();
			const auto key = this->reg.pop();
			const auto ref = this->reg.pop();
			if(isMap(ref)) return insertM(ref, this->heap, key, elem);
			const auto index = toIndex(key);
			if(isStr(ref)) return insertI<String>(ref, this->heap, elem, index);
			if(isArr(ref)) return insertI<Array>(ref, this->heap, elem, index);
			throw except::invalidArgument();
		} break;

		case 2: {
			const auto elem = this->reg.pop();
			const auto ref = this->reg.pop();
			if(isStr(ref)) return insertBack<String>(ref, this->heap, elem);
			if(isArr(ref)) return insertBack<Array>(ref, this->heap, elem);
			throw except::invalidArgument();
		} break;
		
		default:
			throw except::invalidArgument();
			break;
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

		if(isMap(ref)) {
			insertM(ref, this->heap, key, elem);
			return;
		}

		throw except::invalidArgument();
	}
}