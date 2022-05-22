#include "instructions.hxx"
#include "ltnvm/build_in/algorithm.hxx"
#include "ltnvm/build_in/random.hxx"

namespace ltn::vm::inst {
	static constexpr auto make_build_in_table() {
		std::array<Value(*)(VmCore &), 256> table;
		
		std::fill(std::begin(table), std::end(table), [] (auto &) -> Value {
			std::stringstream ss;
			ss << "Illegal Build In Function";
			throw std::runtime_error{ss.str()};
		});

		// algorithm
		table[0x00] = build_in::sort_ascn;
		table[0x01] = build_in::sort_desc;
		table[0x02] = build_in::is_sorted_ascn;
		table[0x03] = build_in::is_sorted_desc;
		table[0x04] = build_in::find;
		table[0x05] = build_in::copy_front;
		table[0x06] = build_in::copy_back;
		table[0x07] = build_in::fill;
		table[0x08] = build_in::reverse;
		
		// random
		table[0x10] = build_in::split;
		table[0x11] = build_in::rand;
		table[0x12] = build_in::rand_int;
		table[0x13] = build_in::rand_float;
		
		return table;
	}

	static const auto build_in_table = make_build_in_table();

	void build_in(VmCore & core) {
		const std::uint16_t byte0 = static_cast<std::uint16_t>(core.fetch_byte());
		const std::uint16_t byte1 = static_cast<std::uint16_t>(core.fetch_byte());
		const std::uint16_t code = (byte0 << 8) + byte1;
		const Value result = build_in_table[code](core);
		core.reg.push(result);
	}
}
