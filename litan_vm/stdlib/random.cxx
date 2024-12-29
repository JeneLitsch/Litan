#include "random.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/utils/convert.hxx"

namespace ltn::vm::stdlib {
	namespace {
		RandomEngine & get_rng(const Value ref) {
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



	Value mersenne_0::func(ltn_Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		const auto seed = std::random_device{}();
		return mersenne(*core, seed);

	}


	
	Value mersenne_1::func(ltn_Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		const auto signed_seed = convert::to_int(args[0]);
		const auto seed = static_cast<std::uint64_t>(signed_seed);
		return mersenne(*core, seed);
	}



	Value split::func(ltn_Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		auto & rng = get_rng(args[0]);
		const auto ref = core->heap.alloc<RandomEngine>(rng.split());
		return value::rng(ref);
	}
	

	Value rand::func(ltn_Context * context, const Value * args) {
		auto & rng = get_rng(args[0]);
		const auto x = rng();
		return value::integer(x);
	}

	Value rand_int::func(ltn_Context * context, const Value * args) {
		auto & rng = get_rng(args[0]);
		const auto min = convert::to_int(args[1]);
		const auto max = convert::to_int(args[2]);
		std::uniform_int_distribution<ltn_Int> dist{
			std::min(min, max),
			std::max(min, max)
		};
		const auto x = rng(dist);
		return value::integer(x);
	}

	Value rand_float::func(ltn_Context * context, const Value * args) {
		auto & rng = get_rng(args[0]);
		const auto min = convert::to_float(args[1]);
		const auto max = convert::to_float(args[2]);
		std::uniform_real_distribution<ltn_Float> dist{
			std::min(min, max),
			std::max(min, max)
		};
		const auto x = rng(dist);
		return value::floating(x);
	}
}