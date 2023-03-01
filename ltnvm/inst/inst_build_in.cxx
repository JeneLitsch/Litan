#include "instructions.hxx"
#include "ltn/fxcodes.hxx"
#include "ltnvm/build_in/algorithm.hxx"
#include "ltnvm/build_in/random.hxx"
#include "ltnvm/build_in/functional.hxx"
#include "ltnvm/build_in/io.hxx"
#include "ltnvm/build_in/math.hxx"
#include "ltnvm/build_in/string.hxx"
#include "ltnvm/build_in/lib.hxx"

namespace ltn::vm::inst {
	static constexpr auto make_build_in_table() {
		struct TableWrapper{
			using Fx = Value(*)(VmCore&);
			constexpr TableWrapper() {
				std::fill(std::begin(array), std::end(array), [] (auto &) -> Value {
					std::stringstream ss;
					ss << "Illegal Build In Function";
					throw std::runtime_error{ss.str()};
				});
			}
			std::array<Fx, 256> array;

			constexpr Fx & operator[](FxCode op_code) {
				return array[static_cast<std::size_t>(op_code)];
			}
		} table;
		


		// algorithm
		table[FxCode::SORT_ASCN] = build_in::sort_ascn;
		table[FxCode::SORT_DESC] = build_in::sort_desc;
		table[FxCode::IS_SORTED_ASCN] = build_in::is_sorted_ascn;
		table[FxCode::IS_SORTED_DESC] = build_in::is_sorted_desc;
		table[FxCode::FIND] = build_in::find;
		table[FxCode::FILL] = build_in::fill;
		table[FxCode::REVERSE] = build_in::reverse;
		
		// random
		table[FxCode::SPLIT] = build_in::split;
		table[FxCode::RAND] = build_in::rand;
		table[FxCode::RAND_INT] = build_in::rand_int;
		table[FxCode::RAND_FLOAT] = build_in::rand_float;

		//functional
		table[FxCode::ARITY] = build_in::arity;

		//io
		table[FxCode::RESET_COLOR] = build_in::reset_color;
		table[FxCode::SET_FG_COLOR] = build_in::set_fg_color;
		table[FxCode::SET_BG_COLOR] = build_in::set_bg_color;

		table[FxCode::TO_STRING] = build_in::to_string;
		table[FxCode::SPLIT_STRING] = build_in::split_string;
		table[FxCode::JOIN_STRING] = build_in::join_string;

		// Math
		table[FxCode::MIN] = build_in::min;
		table[FxCode::MAX] = build_in::max;
		table[FxCode::CLAMP] = build_in::clamp;
		table[FxCode::ROUND] = build_in::round;
		table[FxCode::FLOOR] = build_in::floor;
		table[FxCode::CEIL] = build_in::ceil;
		table[FxCode::ABS] = build_in::abs;
		table[FxCode::SIN] = build_in::sin;
		table[FxCode::COS] = build_in::cos;
		table[FxCode::TAN] = build_in::tan;
		table[FxCode::SQRT] = build_in::sqrt;
		table[FxCode::HYPOT] = build_in::hypot;
		table[FxCode::LOG] = build_in::log;
		table[FxCode::LN] = build_in::ln;
		table[FxCode::LD] = build_in::ld;
		table[FxCode::LG] = build_in::lg;

		table[FxCode::LIB_OPEN] = build_in::lib_open;
		table[FxCode::LIB_CLOSE] = build_in::lib_close;
		table[FxCode::LIB_GET_FX] = build_in::lib_get_fx;
		
		return table.array;
	}

	static const auto build_in_table = make_build_in_table();

	void build_in(VmCore & core) {
		const auto byte0 = static_cast<std::uint32_t>(core.fetch_byte());
		const auto byte1 = static_cast<std::uint32_t>(core.fetch_byte());
		const auto code = (byte0 << 8) + byte1;
		const Value result = build_in_table[code](core);
		core.stack.push(result);
	}
}
