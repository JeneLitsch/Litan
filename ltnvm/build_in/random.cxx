#include "random.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/convert.hxx"

namespace ltn::vm::build_in {
	static RandomEngine & get_rng(const Value ref, Heap & heap) {
		if(is_rng(ref)) {
			return heap.read<RandomEngine>(ref.u);
		}
		else {
			throw except::invalid_argument();
		}
	}


	void split(VmCore & core) {
		auto & rng = get_rng(core.reg.pop(), core.heap);
		const auto ref = core.heap.alloc<RandomEngine>(rng.split());
		core.reg.push(value::rng(ref));
	}
	

	void rand(VmCore & core) {
		auto & rng = get_rng(core.reg.pop(), core.heap);
		const auto x = rng();
		core.reg.push(value::integer(x));
	}

	void rand_int(VmCore & core) {
		const auto max = convert::to_int(core.reg.pop());
		const auto min = convert::to_int(core.reg.pop());
		auto & rng = get_rng(core.reg.pop(), core.heap);
		std::uniform_int_distribution<std::int64_t> dist{
			std::min(min, max),
			std::max(min, max)
		};
		const auto x = dist(rng);
		core.reg.push(value::integer(x));
	}

	void rand_float(VmCore & core) {
		const auto max = convert::to_float(core.reg.pop());
		const auto min = convert::to_float(core.reg.pop());
		auto & rng = get_rng(core.reg.pop(), core.heap);
		std::uniform_real_distribution<stx::float64_t> dist{
			std::min(min, max),
			std::max(min, max)
		};
		const auto x = dist(rng);
		core.reg.push(value::floating(x));
	}
}