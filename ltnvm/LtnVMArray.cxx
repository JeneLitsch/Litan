#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "Stringify.hxx"

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
			string += toString(element, this->heap);
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
			string = toString(element, this->heap) + string;
			return;
		}
		if(isArr(refArray)) {
			auto & array = this->heap.read<Array>(refArray.u).arr;
			array.insert(array.begin(), element);
			return;
		}
		throw std::runtime_error{"Can only append to array or string"};
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
	}  
	

	void LtnVM::remove_back() {
		const auto refArray = this->reg.pop();
		if(isStr(refArray)) {
			auto & string = this->heap.read<String>(refArray.u).str; 
			return removeLast(string);
		}
		if(isArr(refArray)) {
			auto & array = this->heap.read<Array>(refArray.u).arr;
			return removeLast(array);
		}
		throw std::runtime_error{"Can only append to array or string"};
	}

	void LtnVM::remove_front() {
		const auto refArray = this->reg.pop();
		if(isStr(refArray)) {
			auto & string = this->heap.read<String>(refArray.u).str;
			return removeFirst(string);
		}
		if(isArr(refArray)) {
			auto & array = this->heap.read<Array>(refArray.u).arr;
			return removeFirst(array);
		}
		throw std::runtime_error{"Can only append to array or string"};
	}
}