#include "LtnVM.hxx"
#include "type_check.hxx"
#include "convert.hxx"
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
		const auto ptr = this->core.heap.alloc<Array>({});
		auto & arr = this->core.heap.read<Array>(ptr).get(); 
		const auto size = this->fetch_uint();
		pushAll(arr, this->core.reg, size);
		this->core.reg.push({ ptr, Value::Type::ARRAY });
		this->core.heap.collect_garbage(this->core.stack, this->core.reg);
	}


	void LtnVM::newstr() {
		const auto size = this->fetch_uint();
		const auto cstr = this->fetch_str();
		std::string str(cstr, cstr + size); 
		const auto ptr = this->core.heap.alloc<String>({std::move(str)});
		this->core.reg.push({ ptr, Value::Type::STRING });
		this->core.pc += size;
		this->core.heap.collect_garbage(this->core.stack, this->core.reg);
	}


	void LtnVM::newout() {
		const auto add_out = [&] (auto && out) {
			using T = decltype(out)&&;
			const auto ptr = this->core.heap.alloc<OStream>(std::forward<T>(out));
			this->core.reg.push({ ptr, Value::Type::OSTREAM });
			this->core.heap.collect_garbage(this->core.stack, this->core.reg);
		};

		const auto variant = this->fetch_byte();
		switch (variant) {
			case 0: return add_out(OStream{std::cout});
			case 1: {
				const auto openmode = convert::to_int(this->core.reg.pop());
				const auto ref = this->core.reg.pop();
				if(!is_string(ref)) {
					throw except::invalid_argument();
				}
				const auto & path = this->core.heap.read<String>(ref.u).str;

				const auto flags =
					openmode ? std::ios::app : std::ios::trunc;

				auto fout = std::make_unique<std::ofstream>(path, flags);
				return add_out(OStream{std::move(fout)});
			}
			case 2: {
				return add_out(OStream{std::make_unique<std::ostringstream>()});
			}
		}
		throw std::runtime_error{"Unknow output variant"};
	}


	void LtnVM::newin() {
		const auto add_in = [&] (auto && in) {
			using T = decltype(in)&&;
			const auto ptr = this->core.heap.alloc<IStream>(std::forward<T>(in));
			this->core.reg.push({ ptr, Value::Type::ISTREAM });
			this->core.heap.collect_garbage(this->core.stack, this->core.reg);
		};

		const auto variant = this->fetch_byte();
		switch (variant) {
			case 0: return add_in(IStream{std::cin});
			case 1: {
				const auto ref = this->core.reg.pop();
				if(!is_string(ref)) {
					throw except::invalid_argument();
				}
				const auto & path = this->core.heap.read<String>(ref.u).str;
				if(!std::filesystem::exists(path)) {
					throw except::cannot_open_file(path);
				}
				return add_in(IStream{std::make_unique<std::ifstream>(path)});
			}
			case 2: {
				const auto ref = this->core.reg.pop();
				if(!is_string(ref)) {
					throw except::invalid_argument();
				}
				const auto & str = this->core.heap.read<String>(ref.u).str;
				return add_in(IStream{std::make_unique<std::istringstream>(str)});
			}
		}
		throw std::runtime_error {"Unknow input variant"};
	}


	void LtnVM::newclock() {
		const auto ptr = this->core.heap.alloc<Clock>({});
		this->core.reg.push({ ptr, Value::Type::CLOCK });
		this->core.heap.collect_garbage(this->core.stack, this->core.reg);
	}


	void LtnVM::newstruct() {
		const auto ptr = this->core.heap.alloc<Struct>({});
		this->core.reg.push({ ptr, Value::Type::STRUCT });
		this->core.heap.collect_garbage(this->core.stack, this->core.reg);
	}


	void LtnVM::newrange() {
		const auto end = this->core.reg.pop();
		const auto begin = this->core.reg.pop();
		const auto array = this->core.reg.pop();
		
		if(!is_array(array)) throw except::invalid_argument();
		if(!is_int(begin)) throw except::invalid_argument();
		if(!is_int(end))   throw except::invalid_argument();

		const auto size = end.i - begin.i;
		
		const auto & arr = this->core.heap.read<Array>(array.u).get();
		if(size < 0 || size > static_cast<std::int64_t>(arr.size())) {
			throw except::out_of_range();
		}
		
		const auto range = this->core.heap.alloc<Range>({array.u, begin.i, end.i});
		this->core.reg.push(Value{range, Value::Type::RANGE});
	}


	void LtnVM::newstack() {
		const auto ref = this->core.heap.alloc<Deque>({});
		this->core.reg.push({ ref, Value::Type::STACK });
		this->core.heap.collect_garbage(this->core.stack, this->core.reg);
	}


	void LtnVM::newqueue() {
		const auto ref = this->core.heap.alloc<Deque>({});
		this->core.reg.push({ ref, Value::Type::QUEUE });
		this->core.heap.collect_garbage(this->core.stack, this->core.reg);
	}


	void LtnVM::newmap() {
		const auto ref = this->core.heap.alloc<Map>(Map{this->core.heap});
		this->core.reg.push({ ref, Value::Type::MAP });
		this->core.heap.collect_garbage(this->core.stack, this->core.reg);
	}


	void LtnVM::newfx(){
		const auto address = this->fetch_uint(); 
		const auto params = this->fetch_uint();
		const auto ref = this->core.heap.alloc<FxPointer>({address, params, {}});
		this->core.reg.push(Value{ref, Value::Type::FX_PTR});
	}

	void LtnVM::newrng(){
		const auto type = this->fetch_byte();
		switch (type) {
		case 0x00: { 
			const auto seed = std::random_device{}();
			const auto rng = RandomEngine{std::mt19937_64{seed}};
			const auto ref = this->core.heap.alloc<RandomEngine>(rng);
			this->core.reg.push(value::rng(ref));
			return;
		}

		case 0x01: { 
			const auto signed_seed = convert::to_int(this->core.reg.pop());
			const auto seed = static_cast<std::uint64_t>(signed_seed);
			const auto rng = RandomEngine{std::mt19937_64{seed}};
			const auto ref = this->core.heap.alloc<RandomEngine>(rng);
			this->core.reg.push(value::rng(ref));
			return;
		}
		
		default: throw std::runtime_error{"Unknown RandonEngine type"};
		}
	}
}