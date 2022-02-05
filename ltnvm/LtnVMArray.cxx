#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "cast.hxx"

namespace ltn::vm {
	namespace {
		void guardIndex(const auto & collection, auto i) {
			if(i < 0) {
				throw std::runtime_error{"Negative index is not allowed"};
			}
			if(i >= static_cast<decltype(i)>(collection.size())) {
				throw std::runtime_error{"Index out of range"};
			}
		}

		std::int64_t getIndex(Register & reg) {
			const auto index = reg.pop();
			if(!isInt(index)) {
				throw std::runtime_error{"Expected integer as index"};
			}
			return index.i;
		}
	}

	void LtnVM::size() {
		const auto ref = this->reg.pop();
		if (isArr(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u);
			this->reg.push(static_cast<std::int64_t>(arr.arr.size()));
			return;
		}
		if(isStr(ref)) {
			const auto & str = this->heap.read<String>(ref.u);
			this->reg.push(static_cast<std::int64_t>(str.str.size()));
			return;
		}
		if(isFxPtr(ref)) {
			const auto & fxPtr = this->heap.read<FxPointer>(ref.u);
			this->reg.push(static_cast<std::int64_t>(fxPtr.params));
			return;
		}
		if(isRange(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(range.end - range.begin);
			return;
		}
		this->reg.push(static_cast<std::int64_t>(0));
	}

	void LtnVM::front() {
		const auto ref = this->reg.pop();
		if (isArr(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u);
			this->reg.push(arr.arr.front());
		}
		else {
			throw std::runtime_error{"Cannot get front element from non array type"};
		}
	}
	
	void LtnVM::back() {
		const auto ref = this->reg.pop();
		if (isArr(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u);
			this->reg.push(arr.arr.back());
		}
		else {
			throw std::runtime_error{"Cannot get back element from non array type"};
		}
	}

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
	}

	void LtnVM::insert() {
		const auto type = this->fetchByte();

		switch (type) {
		case 0: {
			const auto elem = this->reg.pop();
			const auto ref = this->reg.pop();
			if(isStr(ref)) return insertFront<String>(ref, this->heap, elem);
			if(isArr(ref)) return insertFront<Array>(ref, this->heap, elem);
			throw std::runtime_error{"Can only append to array or string"};
		} break;

		case 1: {
			const auto elem = this->reg.pop();
			const auto index = getIndex(this->reg);
			const auto ref = this->reg.pop();
			if(isStr(ref)) return insertI<String>(ref, this->heap, elem, index);
			if(isArr(ref)) return insertI<Array>(ref, this->heap, elem, index);
			throw std::runtime_error{"Can only append to a collection type"};
		} break;

		case 2: {
			const auto elem = this->reg.pop();
			const auto ref = this->reg.pop();
			if(isStr(ref)) return insertBack<String>(ref, this->heap, elem);
			if(isArr(ref)) return insertBack<Array>(ref, this->heap, elem);
			throw std::runtime_error{"Can only append to array or string"};
		} break;
		
		default:
			throw std::runtime_error{"Invalid insert type"};
			break;
		}

	}
	
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
		void removeIndex(const Value ref, Heap & heap, std::int64_t index) {
			auto & collection = heap.read<Collection>(ref.u).get(); 
			if(index < 0) {
				throw std::runtime_error{"Negative idex is not allowed"};
			}
			if(collection.size() <= static_cast<std::size_t>(index)) {
				throw std::runtime_error{"Index out of range"};
			}
			collection.erase(collection.begin() + index);
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
			const auto index = getIndex(this->reg);
			const auto ref = this->reg.pop();
			if(isStr(ref)) return removeIndex<String>(ref, this->heap, index);
			if(isArr(ref)) return removeIndex<Array>(ref, this->heap, index);
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

	namespace {
		auto iterator(auto i) {
			return Value(static_cast<std::int64_t>(i));
		}
	}

	void LtnVM::begin() {
		const auto ref = this->reg.pop();
		if(isArr(ref)) {
			this->reg.push(iterator(0));
			return;
		}

		if(isRange(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(iterator(range.begin));
			return;
		}

		throw std::runtime_error{"Can only get iterator from Array or Range"};
	}

	void LtnVM::end() {
		const auto ref = this->reg.pop();
		if(isArr(ref)) {
			const auto & array = this->heap.read<Array>(ref.u);
			this->reg.push(iterator(array.arr.size()));
			return;
		}

		if(isRange(ref)) {
			const auto & range = this->heap.read<Range>(ref.u);
			this->reg.push(iterator(range.end));
			return;
		}

		throw std::runtime_error{"Can only get iterator from Array or Range"};
	}
}