#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace ltn::vm {
	void LtnVM::newarr(){
		const auto ptr = this->heap.alloc<Array>({});
		this->reg.push({ ptr, Value::Type::ARRAY });
		this->heap.collectGarbage(this->stack, this->reg);
	}
	void LtnVM::newstr() {
		const auto ptr = this->heap.alloc<String>({});
		this->reg.push({ ptr, Value::Type::STRING });
		this->heap.collectGarbage(this->stack, this->reg);
	}
	void LtnVM::newout() {
		const auto addOut = [&] (auto && out) {
			using T = decltype(out)&&;
			const auto ptr = this->heap.alloc<OStream>(std::forward<T>(out));
			this->reg.push({ ptr, Value::Type::OSTREAM });
			this->heap.collectGarbage(this->stack, this->reg);
		};

		const auto variant = this->fetchByte();
		switch (variant) {
			case 0: return addOut(OStream{std::cout});
			case 1: {
				const auto ref = this->reg.pop();
				if(!isStr(ref)) {
					throw std::runtime_error{"Filestream needs path as string"};
				}
				const auto & path = this->heap.read<String>(ref.u).str;
				return addOut(OStream{std::make_unique<std::ofstream>(path)});
			}
		}
		throw std::runtime_error {"Unknow output variant"};
	}
	void LtnVM::newin() {
		const auto addIn = [&] (auto && in) {
			using T = decltype(in)&&;
			const auto ptr = this->heap.alloc<IStream>(std::forward<T>(in));
			this->reg.push({ ptr, Value::Type::ISTREAM });
			this->heap.collectGarbage(this->stack, this->reg);
		};

		const auto variant = this->fetchByte();
		switch (variant) {
			case 0: return addIn(IStream{std::cin});
			case 1: {
				const auto ref = this->reg.pop();
				if(!isStr(ref)) {
					throw std::runtime_error{"Filestream needs path as string"};
				}
				const auto & path = this->heap.read<String>(ref.u).str;
				if(!std::filesystem::exists(path)) {
					throw std::runtime_error{"Cannot open fin \"" + path + "\""};
				}
				return addIn(IStream{std::make_unique<std::ifstream>(path)});
			}
		}
		throw std::runtime_error {"Unknow input variant"};
	}
	void LtnVM::newClock() {
		const auto ptr = this->heap.alloc<Clock>({});
		this->reg.push({ ptr, Value::Type::CLOCK });
		this->heap.collectGarbage(this->stack, this->reg);
	}
}