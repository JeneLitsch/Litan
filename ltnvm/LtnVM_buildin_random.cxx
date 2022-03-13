#include "LtnVM.hxx"
#include <random>
#include "convert.hxx"

namespace ltn::vm {
	namespace {
		RandomEngine & get_rng(const Value ref, Heap & heap) {
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


		void rand(Register & reg, Heap & heap) {
			auto & rng = get_rng(reg.pop(), heap);
			const auto x = rng();
			reg.push(value::integer(x));
		}

		void rand_int(Register & reg, Heap & heap) {
			const auto max = convert::to_int(reg.pop());
			const auto min = convert::to_int(reg.pop());
			auto & rng = get_rng(reg.pop(), heap);
			std::uniform_int_distribution<std::int64_t> dist{min, max};
			const auto x = dist(rng);
			reg.push(value::integer(x));
		}

		void rand_float(Register & reg, Heap & heap) {
			const auto max = convert::to_float(reg.pop());
			const auto min = convert::to_float(reg.pop());
			auto & rng = get_rng(reg.pop(), heap);
			std::uniform_real_distribution<stx::float64_t> dist{min, max};
			const auto x = dist(rng);
			reg.push(value::floating(x));
		}

	}
	
	void LtnVM::random() {
		const auto func = this->fetch_byte();
		switch (func) {
		case 0x00: return init_seed(this->reg, this->heap);
		case 0x01: return seed(this->reg, this->heap);
		case 0x10: return rand(this->reg, this->heap);
		case 0x11: return rand_int(this->reg, this->heap);
		case 0x12: return rand_float(this->reg, this->heap);
		
		default: throw std::runtime_error{"Invalid random func code"};
		}
	}
}