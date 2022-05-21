#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/convert.hxx"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace ltn::vm::inst {

	void pushAll(auto & array, Register & reg, std::uint64_t size) {
		if(!size) return;
		const auto value = reg.pop();
		pushAll(array, reg, size -1);
		array.push_back(value);
	} 

	void newarr(VmCore & core){
		const auto ptr = core.heap.alloc<Array>({});
		auto & arr = core.heap.read<Array>(ptr).get(); 
		const auto size = core.fetch_uint();
		pushAll(arr, core.reg, size);
		core.reg.push({ ptr, Value::Type::ARRAY });
		core.heap.collect_garbage(core.stack, core.reg);
	}


	void newstr(VmCore & core) {
		const auto size = core.fetch_uint();
		const auto cstr = core.fetch_str();
		std::string str(cstr, cstr + size); 
		const auto ptr = core.heap.alloc<String>({std::move(str)});
		core.reg.push({ ptr, Value::Type::STRING });
		core.pc += size;
		core.heap.collect_garbage(core.stack, core.reg);
	}


	void newout(VmCore & core) {
		const auto add_out = [&] (auto && out) {
			using T = decltype(out)&&;
			const auto ptr = core.heap.alloc<OStream>(std::forward<T>(out));
			core.reg.push({ ptr, Value::Type::OSTREAM });
			core.heap.collect_garbage(core.stack, core.reg);
		};

		const auto variant = core.fetch_byte();
		switch (variant) {
			case 0: return add_out(OStream{std::cout});
			case 1: {
				const auto openmode = convert::to_int(core.reg.pop());
				const auto ref = core.reg.pop();
				if(!is_string(ref)) {
					throw except::invalid_argument();
				}
				const auto & path = core.heap.read<String>(ref.u).str;

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


	void newin(VmCore & core) {
		const auto add_in = [&] (auto && in) {
			using T = decltype(in)&&;
			const auto ptr = core.heap.alloc<IStream>(std::forward<T>(in));
			core.reg.push({ ptr, Value::Type::ISTREAM });
			core.heap.collect_garbage(core.stack, core.reg);
		};

		const auto variant = core.fetch_byte();
		switch (variant) {
			case 0: return add_in(IStream{std::cin});
			case 1: {
				const auto ref = core.reg.pop();
				if(!is_string(ref)) {
					throw except::invalid_argument();
				}
				const auto & path = core.heap.read<String>(ref.u).str;
				if(!std::filesystem::exists(path)) {
					throw except::cannot_open_file(path);
				}
				return add_in(IStream{std::make_unique<std::ifstream>(path)});
			}
			case 2: {
				const auto ref = core.reg.pop();
				if(!is_string(ref)) {
					throw except::invalid_argument();
				}
				const auto & str = core.heap.read<String>(ref.u).str;
				return add_in(IStream{std::make_unique<std::istringstream>(str)});
			}
		}
		throw std::runtime_error {"Unknow input variant"};
	}


	void newclock(VmCore & core) {
		const auto ptr = core.heap.alloc<Clock>({});
		core.reg.push({ ptr, Value::Type::CLOCK });
		core.heap.collect_garbage(core.stack, core.reg);
	}


	void newstruct(VmCore & core) {
		const auto ptr = core.heap.alloc<Struct>({});
		core.reg.push({ ptr, Value::Type::STRUCT });
		core.heap.collect_garbage(core.stack, core.reg);
	}


	void newrange(VmCore & core) {
		const auto end = core.reg.pop();
		const auto begin = core.reg.pop();
		const auto array = core.reg.pop();
		
		if(!is_array(array)) throw except::invalid_argument();
		if(!is_int(begin)) throw except::invalid_argument();
		if(!is_int(end))   throw except::invalid_argument();

		const auto size = end.i - begin.i;
		
		const auto & arr = core.heap.read<Array>(array.u).get();
		if(size < 0 || size > static_cast<std::int64_t>(arr.size())) {
			throw except::out_of_range();
		}
		
		const auto range = core.heap.alloc<Range>({array.u, begin.i, end.i});
		core.reg.push(Value{range, Value::Type::RANGE});
	}


	void newstack(VmCore & core) {
		const auto ref = core.heap.alloc<Deque>({});
		core.reg.push({ ref, Value::Type::STACK });
		core.heap.collect_garbage(core.stack, core.reg);
	}


	void newqueue(VmCore & core) {
		const auto ref = core.heap.alloc<Deque>({});
		core.reg.push({ ref, Value::Type::QUEUE });
		core.heap.collect_garbage(core.stack, core.reg);
	}


	void newmap(VmCore & core) {
		const auto ref = core.heap.alloc<Map>(Map{core.heap});
		core.reg.push({ ref, Value::Type::MAP });
		core.heap.collect_garbage(core.stack, core.reg);
	}


	void newfx(VmCore & core){
		const auto address = core.fetch_uint(); 
		const auto params = core.fetch_uint();
		const auto ref = core.heap.alloc<FxPointer>({address, params, {}});
		core.reg.push(Value{ref, Value::Type::FX_PTR});
	}

	void newrng(VmCore & core){
		const auto type = core.fetch_byte();
		switch (type) {
		case 0x00: { 
			const auto seed = std::random_device{}();
			const auto rng = RandomEngine{std::mt19937_64{seed}};
			const auto ref = core.heap.alloc<RandomEngine>(rng);
			core.reg.push(value::rng(ref));
			return;
		}

		case 0x01: { 
			const auto signed_seed = convert::to_int(core.reg.pop());
			const auto seed = static_cast<std::uint64_t>(signed_seed);
			const auto rng = RandomEngine{std::mt19937_64{seed}};
			const auto ref = core.heap.alloc<RandomEngine>(rng);
			core.reg.push(value::rng(ref));
			return;
		}
		
		default: throw std::runtime_error{"Unknown RandonEngine type"};
		}
	}
}