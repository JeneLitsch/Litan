#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "cast.hxx"

namespace ltn::vm {
	void LtnVM::size() {
		const auto ref = this->reg.pop();
		if (isArr(ref)) {
			const auto & arr = this->heap.read<Array>(ref.u);
			this->reg.push(static_cast<std::int64_t>(arr.arr.size()));
		}
		else if(isStr(ref)) {
			const auto & str = this->heap.read<String>(ref.u);
			this->reg.push(static_cast<std::int64_t>(str.str.size()));
		}
		else if(isFxPtr(ref)) {
			const auto & fxPtr = this->heap.read<FxPointer>(ref.u);
			this->reg.push(static_cast<std::int64_t>(fxPtr.params));
		}
		else {
			this->reg.push(static_cast<std::int64_t>(0));
		}
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

	void LtnVM::insert_back() {
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
	}

	void LtnVM::insert_front() {
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
	}

	void LtnVM::insert() {
		const auto element = this->reg.pop();
		const auto index = this->reg.pop();
		const auto refCollection = this->reg.pop();
		if(!isInt(index)) {
			throw std::runtime_error{"Expected integer as index"};
		}
		if(isStr(refCollection)) {
			auto & string = this->heap.read<String>(refCollection.u).str;
			const auto str = cast::to_string(element, this->heap); 
			string.insert(index.i, str);
			return;
		}
		if(isArr(refCollection)) {
			auto & array = this->heap.read<Array>(refCollection.u).arr;
			array.insert(array.begin() + index.i, element);
			return;
		}
		throw std::runtime_error{"Can only append to a collection type"};
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
	

	void LtnVM::remove_back() {
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
	}

	void LtnVM::remove_front() {
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
	}

	void LtnVM::remove() {
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
	}
}