#include "LtnVM.hxx"
#include <random>
#include "convert.hxx"

namespace ltn::vm {
	namespace {
		RandomEngine & get_rng(const Value & ref, Heap & heap) {
			if(is_rng(ref)) {
				return heap.read<RandomEngine>(ref.u);
			}
			else {
				throw except::invalid_argument();
			}
		}


		void init_seed(Register & reg, Heap & heap) {
			auto & rng = get_rng(reg.pop(), heap);
			std::random_device rng_dev;
			rng.seed(rng_dev());
		}


		void seed(Register & reg, Heap & heap) {
			const auto seed = convert::to_int(reg.pop());
			auto & rng = get_rng(reg.pop(), heap);
			rng.seed(seed);
		}


		void get(Register & reg, Heap & heap) {
			auto & rng = get_rng(reg.pop(), heap);
			const auto x = rng.get();
			reg.push(value::integer(x));
		}
	}
	
	void LtnVM::random() {
		const auto func = this->fetch_byte();
		switch (func) {
		case 0x00: return init_seed(this->reg, this->heap);
		case 0x01: return seed(this->reg, this->heap);
		case 0x10: return get(this->reg, this->heap);
		
		default:
			break;
		}
	}
}