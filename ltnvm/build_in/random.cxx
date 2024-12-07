#include "random.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/convert.hxx"

namespace ltn::vm::build_in::random {
	namespace {
		RandomEngine & get_rng(const Value ref, Heap & heap) {
			if(is_rng(ref)) {
				return *value::as<RandomEngine>(ref);
			}
			else {
				throw except::invalid_argument();
			}
		}



		Value mersenne(VMCore & core, std::uint64_t seed) {
			core.heap.collect_garbage(core.stack);
			const auto ptr = core.heap.alloc(RandomEngine{std::mt19937_64{seed}});
			const auto val = value::rng(ptr); 
			return val;
		}
	}



	Value mersenne_0(VMCore & core) {
		const auto seed = std::random_device{}();
		return mersenne(core, seed);

	}


	
	Value mersenne_1(VMCore & core) {
		const auto signed_seed = convert::to_int(core.stack.pop());
		const auto seed = static_cast<std::uint64_t>(signed_seed);
		return mersenne(core, seed);
	}



	Value split(VMCore & core) {
		auto & rng = get_rng(core.stack.pop(), core.heap);
		const auto ref = core.heap.alloc<RandomEngine>(rng.split());
		return value::rng(ref);
	}
	

	Value rand(VMCore & core) {
		auto & rng = get_rng(core.stack.pop(), core.heap);
		const auto x = rng();
		return value::integer(x);
	}

	Value rand_int(VMCore & core) {
		const auto max = convert::to_int(core.stack.pop());
		const auto min = convert::to_int(core.stack.pop());
		auto & rng = get_rng(core.stack.pop(), core.heap);
		std::uniform_int_distribution<std::int64_t> dist{
			std::min(min, max),
			std::max(min, max)
		};
		const auto x = rng(dist);
		return value::integer(x);
	}

	Value rand_float(VMCore & core) {
		const auto max = convert::to_float(core.stack.pop());
		const auto min = convert::to_float(core.stack.pop());
		auto & rng = get_rng(core.stack.pop(), core.heap);
		std::uniform_real_distribution<stx::float64_t> dist{
			std::min(min, max),
			std::max(min, max)
		};
		const auto x = rng(dist);
		return value::floating(x);
	}
}