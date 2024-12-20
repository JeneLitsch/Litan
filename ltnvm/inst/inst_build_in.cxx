#include "instructions.hxx"
#include "ltn/fxcodes.hxx"
#include "ltnvm/build_in/algorithm.hxx"
#include "ltnvm/build_in/chrono.hxx"
#include "ltnvm/build_in/container.hxx"
#include "ltnvm/build_in/random.hxx"
#include "ltnvm/build_in/functional.hxx"
#include "ltnvm/build_in/io.hxx"
#include "ltnvm/build_in/iter.hxx"
#include "ltnvm/build_in/json.hxx"
#include "ltnvm/build_in/math.hxx"
#include "ltnvm/build_in/string.hxx"
#include "ltnvm/build_in/type.hxx"
#include "ltnvm/build_in/plugin.hxx"



namespace ltn::vm::inst {
	static constexpr auto make_build_in_table() {
		struct TableWrapper{
			using Fx = Value(*)(VMCore&);
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
		table[FxCode::ALGORITHM_REDUCE_L_2] = build_in::reduce_l_2;
		table[FxCode::ALGORITHM_REDUCE_L_3] = build_in::reduce_l_3;

		
		// random
		table[FxCode::RANDOM_SPLIT]      = build_in::random::split;
		table[FxCode::RANDOM_RAND]       = build_in::random::rand;
		table[FxCode::RANDOM_RAND_INT]   = build_in::random::rand_int;
		table[FxCode::RANDOM_RAND_FLOAT] = build_in::random::rand_float;
		table[FxCode::RANDOM_MERSENNE_0] = build_in::random::mersenne_0;
		table[FxCode::RANDOM_MERSENNE_1] = build_in::random::mersenne_1;

		//functional
		table[FxCode::FX_ARITY] = build_in::arity;
		table[FxCode::FX_INVOKE] = build_in::invoke;
		table[FxCode::FX_IS_VARIADIC] = build_in::is_variadic;

		//io
		table[FxCode::IO_RESET_COLOR] = build_in::io::reset_color;
		table[FxCode::IO_SET_FG_COLOR] = build_in::io::set_fg_color;
		table[FxCode::IO_SET_BG_COLOR] = build_in::io::set_bg_color;
		table[FxCode::IO_IS_EOF] = build_in::io::is_eof;
		table[FxCode::IO_CLOSE_STREAM] = build_in::io::close_stream;
		table[FxCode::IO_PRINT] = build_in::io::print;
		table[FxCode::IO_READ_STR] = build_in::io::read_str;
		table[FxCode::IO_READ_LINE] = build_in::io::read_line;
		table[FxCode::IO_READ_BOOL] = build_in::io::read_bool;
		table[FxCode::IO_READ_CHAR] = build_in::io::read_char;
		table[FxCode::IO_READ_INT] = build_in::io::read_int;
		table[FxCode::IO_READ_FLOAT] = build_in::io::read_float;
		table[FxCode::IO_READ_ALL] = build_in::io::read_all;

		table[FxCode::IO_COUT] = build_in::io::cout;
		table[FxCode::IO_FOUT] = build_in::io::fout;
		table[FxCode::IO_STROUT] = build_in::io::strout;
		table[FxCode::IO_CIN] = build_in::io::cin;
		table[FxCode::IO_FIN] = build_in::io::fin;
		table[FxCode::IO_STRIN] = build_in::io::strin;

		table[FxCode::JSON_PARSE] = build_in::json::parse;
		table[FxCode::JSON_PRINT] = build_in::json::print;

		// string
		table[FxCode::TO_STRING] = build_in::to_string;
		table[FxCode::SPLIT_STRING] = build_in::split_string;

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

		table[FxCode::TYPE_ID] = build_in::type::id;
		table[FxCode::TYPE_CLONE] = build_in::type::clone;
		table[FxCode::TYPE_IS] = build_in::type::is;
		table[FxCode::TYPE_CAST] = build_in::type::cast;
		table[FxCode::TYPE_QUEUE] = build_in::type::queue;
		table[FxCode::TYPE_STACK] = build_in::type::stack;
		table[FxCode::TYPE_MAP] = build_in::type::map;

		table[FxCode::ITER_RANGE] = build_in::iter::range;
		table[FxCode::ITER_NEXT] = build_in::iter::next;
		table[FxCode::ITER_GET] = build_in::iter::get;
		table[FxCode::ITER_MOVE] = build_in::iter::move;
		table[FxCode::ITER_ITER] = build_in::iter::iter;
		table[FxCode::ITER_IS_STOP] = build_in::iter::is_stop;
		table[FxCode::ITER_COMBINED] = build_in::iter::combined;
		table[FxCode::ITER_REVERSED] = build_in::iter::reversed;

		table[FxCode::CHRONO_CLOCK] = build_in::chrono::clock;
		table[FxCode::CHRONO_TO_SECONDS] = build_in::chrono::to_seconds;
		table[FxCode::CHRONO_TO_MILLI_SECONDS] = build_in::chrono::to_milliseconds;

		// Container
		table[FxCode::INSERT_FRONT] = build_in::insert_front;
		table[FxCode::INSERT_BACK] = build_in::insert_back;
		table[FxCode::INSERT] = build_in::insert;
		table[FxCode::REMOVE_FRONT] = build_in::remove_front;
		table[FxCode::REMOVE_BACK] = build_in::remove_back;
		table[FxCode::REMOVE] = build_in::remove;

		table[FxCode::PUSH] = build_in::push;
		table[FxCode::POP] = build_in::pop;
		table[FxCode::PEEK] = build_in::peek;
		table[FxCode::CONTAINS] = build_in::contains;
		table[FxCode::SIZE] = build_in::size;
		table[FxCode::EMPTY] = build_in::empty;
		table[FxCode::AT] = build_in::at;
		table[FxCode::FRONT] = build_in::front;
		table[FxCode::BACK] = build_in::back;

		table[FxCode::LOAD_PLUGIN] = build_in::load_plugin;
		
		return table.array;
	}

	static constexpr auto build_in_table = make_build_in_table();

	void build_in(VMCore & core) {
		const auto byte0 = static_cast<std::uint32_t>(core.fetch_byte());
		const auto byte1 = static_cast<std::uint32_t>(core.fetch_byte());
		const auto code = (byte0 << 8) + byte1;
		const Value result = build_in_table[code](core);
		core.stack.push(result);
	}
}
