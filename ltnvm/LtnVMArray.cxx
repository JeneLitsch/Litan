#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "cast.hxx"

namespace ltn::vm {
	namespace {
		void guardIndex(const auto & container, auto i) {
			if(i < 0) {
				throw std::runtime_error{"Negative index is not allowed"};
			}
			if(i >= static_cast<decltype(i)>(container.size())) {
				throw std::runtime_error{"Index out of range"};
			}
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

	void LtnVM::insert() {
		const auto type = this->fetchByte();

		switch (type) {
		case 0: {
			const auto element = this->reg.pop();
			const auto refArray = this->reg.pop();
			if(isStr(refArray)) {
				auto & string = this->heap.read<String>(refArray.u).str; 
				string = cast::to_string(element, this->heap) + string;
				return;
			}
			if(isArr(refArray)) {
				auto & array = this->heap.read<Array>(refArray.u).arr;
				array.insert(array.begin(), element);
				return;
			}
			throw std::runtime_error{"Can only append to array or string"};
		} break;

		case 1: {
			const auto element = this->reg.pop();
			const auto index = this->reg.pop();
			const auto refCollection = this->reg.pop();
			if(!isInt(index)) {
				throw std::runtime_error{"Expected integer as index"};
			}
			if(isStr(refCollection)) {
				auto & string = this->heap.read<String>(refCollection.u).str;
				const auto str = cast::to_string(element, this->heap);
				guardIndex(str, index.i);
				string.insert(static_cast<std::size_t>(index.i), str);
				return;
			}
			if(isArr(refCollection)) {
				auto & arr = this->heap.read<Array>(refCollection.u).arr;
				guardIndex(arr, index.i);
				arr.insert(arr.begin() + index.i, element);
				return;
			}
			throw std::runtime_error{"Can only append to a collection type"};
		} break;

		case 2: {
			const auto element = this->reg.pop();
			const auto refArray = this->reg.pop();
			if(isStr(refArray)) {
				auto & string = this->heap.read<String>(refArray.u).str; 
				string += cast::to_string(element, this->heap);
				return;
			}
			if(isArr(refArray)) {
				auto & array = this->heap.read<Array>(refArray.u).arr;
				array.push_back(element);
				return;
			}
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

		void removeLast(auto & collection) {
			guardEmpty(collection);
			collection.pop_back();
		}

		void removeFirst(auto & collection) {
			guardEmpty(collection);
			collection.erase(collection.begin());
		}

		void removeIndex(auto & collection, auto index) {
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
			const auto refCollection = this->reg.pop();
			if(isStr(refCollection)) {
				auto & string = this->heap.read<String>(refCollection.u).str;
				return removeFirst(string);
			}
			if(isArr(refCollection)) {
				auto & array = this->heap.read<Array>(refCollection.u).arr;
				return removeFirst(array);
			}
			throw std::runtime_error{"Can only remove from a collection"};
		} break;

		case 1: {
			const auto index = this->reg.pop();
			const auto refCollection = this->reg.pop();
			if(!isInt(index)) {
				throw std::runtime_error{"Expected integer as index"};
			}
			if(isStr(refCollection)) {
				auto & string = this->heap.read<String>(refCollection.u).str;
				return removeIndex(string, index.i);
			}
			if(isArr(refCollection)) {
				auto & array = this->heap.read<Array>(refCollection.u).arr;
				return removeIndex(array, index.i);
			}
			throw std::runtime_error{"Can only remove from a collection"};
		} break;

		case 2: {
			const auto refCollection = this->reg.pop();
			if(isStr(refCollection)) {
				auto & string = this->heap.read<String>(refCollection.u).str; 
				return removeLast(string);
			}
			if(isArr(refCollection)) {
				auto & array = this->heap.read<Array>(refCollection.u).arr;
				return removeLast(array);
			}
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