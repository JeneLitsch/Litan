#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace ltn::vm {

	void pushAll(auto & array, Register & reg, std::uint64_t size) {
		if(!size) return;
		const auto value = reg.pop();
		pushAll(array, reg, size -1);
		array.push_back(value);
	} 

	void LtnVM::newarr(){
		const auto ptr = this->heap.alloc<Array>({});
		auto & arr = this->heap.read<Array>(ptr).get(); 
		const auto size = this->fetch_uint();
		pushAll(arr, this->reg, size);
		this->reg.push({ ptr, Value::Type::ARRAY });
		this->heap.collect_garbage(this->stack, this->reg);
	}


	void LtnVM::newstr() {
		const auto size = this->fetch_uint();
		const auto cstr = this->fetch_str();
		std::string str(cstr, cstr + size); 
		const auto ptr = this->heap.alloc<String>({std::move(str)});
		this->reg.push({ ptr, Value::Type::STRING });
		this->pc += size;
		this->heap.collect_garbage(this->stack, this->reg);
	}


	void LtnVM::newout() {
		const auto addOut = [&] (auto && out) {
			using T = decltype(out)&&;
			const auto ptr = this->heap.alloc<OStream>(std::forward<T>(out));
			this->reg.push({ ptr, Value::Type::OSTREAM });
			this->heap.collect_garbage(this->stack, this->reg);
		};

		const auto variant = this->fetch_byte();
		switch (variant) {
			case 0: return addOut(OStream{std::cout});
			case 1: {
				const auto ref = this->reg.pop();
				if(!is_string(ref)) {
					throw except::invalid_argument();
				}
				const auto & path = this->heap.read<String>(ref.u).str;
				return addOut(OStream{std::make_unique<std::ofstream>(path)});
			}
		}
		throw std::runtime_error{"Unknow output variant"};
	}


	void LtnVM::newin() {
		const auto addIn = [&] (auto && in) {
			using T = decltype(in)&&;
			const auto ptr = this->heap.alloc<IStream>(std::forward<T>(in));
			this->reg.push({ ptr, Value::Type::ISTREAM });
			this->heap.collect_garbage(this->stack, this->reg);
		};

		const auto variant = this->fetch_byte();
		switch (variant) {
			case 0: return addIn(IStream{std::cin});
			case 1: {
				const auto ref = this->reg.pop();
				if(!is_string(ref)) {
					throw except::invalid_argument();
				}
				const auto & path = this->heap.read<String>(ref.u).str;
				if(!std::filesystem::exists(path)) {
					throw except::cannot_open_file(path);
				}
				return addIn(IStream{std::make_unique<std::ifstream>(path)});
			}
		}
		throw std::runtime_error {"Unknow input variant"};
	}


	void LtnVM::newclock() {
		const auto ptr = this->heap.alloc<Clock>({});
		this->reg.push({ ptr, Value::Type::CLOCK });
		this->heap.collect_garbage(this->stack, this->reg);
	}


	void LtnVM::newstruct() {
		const auto ptr = this->heap.alloc<Struct>({});
		this->reg.push({ ptr, Value::Type::STRUCT });
		this->heap.collect_garbage(this->stack, this->reg);
	}


	void LtnVM::newrange() {
		const auto end = this->reg.pop();
		const auto begin = this->reg.pop();
		const auto array = this->reg.pop();
		
		if(!is_array(array)) throw except::invalid_argument();
		if(!is_int(begin)) throw except::invalid_argument();
		if(!is_int(end))   throw except::invalid_argument();
		
		const auto range = this->heap.alloc<Range>({array.u, begin.i, end.i});
		this->reg.push(Value{range, Value::Type::RANGE});
	}


	void LtnVM::newstack() {
		const auto ref = this->heap.alloc<Deque>({});
		this->reg.push({ ref, Value::Type::STACK });
		this->heap.collect_garbage(this->stack, this->reg);
	}


	void LtnVM::newqueue() {
		const auto ref = this->heap.alloc<Deque>({});
		this->reg.push({ ref, Value::Type::QUEUE });
		this->heap.collect_garbage(this->stack, this->reg);
	}


	void LtnVM::newmap() {
		const auto ref = this->heap.alloc<Map>(Map{this->heap});
		this->reg.push({ ref, Value::Type::MAP });
		this->heap.collect_garbage(this->stack, this->reg);
	}


	void LtnVM::newfx(){
		const auto address = this->fetch_uint(); 
		const auto params = this->fetch_uint();
		const auto ref = this->heap.alloc<FxPointer>({address, params, {}});
		this->reg.push(Value{ref, Value::Type::FX_PTR});
	}
}