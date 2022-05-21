#include "instructions.hxx"
#include <random>
#include "ltnvm/convert.hxx"

namespace ltn::vm::inst {
	namespace {
		RandomEngine & get_rng(const Value ref, Heap & heap) {
			if(is_rng(ref)) {
				return heap.read<RandomEngine>(ref.u);
			}
			else {
				throw except::invalid_argument();
			}
		}


		void split(Register & reg, Heap & heap) {
			auto & rng = get_rng(reg.pop(), heap);
			const auto ref = heap.alloc<RandomEngine>(rng.split());
			reg.push(value::rng(ref));
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
			std::uniform_int_distribution<std::int64_t> dist{
				std::min(min, max),
				std::max(min, max)
			};
			const auto x = dist(rng);
			reg.push(value::integer(x));
		}

		void rand_float(Register & reg, Heap & heap) {
			const auto max = convert::to_float(reg.pop());
			const auto min = convert::to_float(reg.pop());
			auto & rng = get_rng(reg.pop(), heap);
			std::uniform_real_distribution<stx::float64_t> dist{
				std::min(min, max),
				std::max(min, max)
			};
			const auto x = dist(rng);
			reg.push(value::floating(x));
		}

	}
	
	void random(VmCore & core) {
		const auto func = core.fetch_byte();
		switch (func) {
		case 0x00: return split(core.reg, core.heap);
		case 0x10: return rand(core.reg, core.heap);
		case 0x11: return rand_int(core.reg, core.heap);
		case 0x12: return rand_float(core.reg, core.heap);
		
		default: throw std::runtime_error{"Invalid random func code"};
		}
	}
}