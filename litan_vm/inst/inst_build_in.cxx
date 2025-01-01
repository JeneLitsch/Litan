#include "litan_core/fxcodes.hxx"

#include "litan_vm/stdlib/misc.hxx"
#include "litan_vm/stdlib/algorithm.hxx"
#include "litan_vm/stdlib/chrono.hxx"
#include "litan_vm/stdlib/container.hxx"
#include "litan_vm/stdlib/io.hxx"
#include "litan_vm/stdlib/string.hxx"
#include "litan_vm/stdlib/json.hxx"
#include "litan_vm/stdlib/functional.hxx"
#include "litan_vm/stdlib/math.hxx"
#include "litan_vm/stdlib/map.hxx"
#include "litan_vm/stdlib/plugin.hxx"
#include "litan_vm/stdlib/random.hxx"
#include "litan_vm/stdlib/type.hxx"
#include "litan_vm/stdlib/iter.hxx"
#include "litan_vm/stdlib/stack.hxx"
#include "litan_vm/stdlib/queue.hxx"



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
		table[FxCode::SORT_ASCN]         = as_build_in<stdlib::sort_ascn>;
		table[FxCode::SORT_DESC]         = as_build_in<stdlib::sort_desc>;
		table[FxCode::IS_SORTED_ASCN]    = as_build_in<stdlib::is_sorted_ascn>;
		table[FxCode::IS_SORTED_DESC]    = as_build_in<stdlib::is_sorted_desc>;
		table[FxCode::FIND]              = as_build_in<stdlib::find>;
		table[FxCode::FILL]              = as_build_in<stdlib::fill>;
		table[FxCode::REVERSE]           = as_build_in<stdlib::reverse>;
		table[FxCode::REDUCE_L_2]        = as_build_in<stdlib::reduce_l_2>;
		table[FxCode::REDUCE_L_3]        = as_build_in<stdlib::reduce_l_3>;
		
		// random
		table[FxCode::RANDOM_SPLIT]      = as_build_in<stdlib::split>;
		table[FxCode::RANDOM_RAND]       = as_build_in<stdlib::rand>;
		table[FxCode::RANDOM_RAND_INT]   = as_build_in<stdlib::rand_int>;
		table[FxCode::RANDOM_RAND_FLOAT] = as_build_in<stdlib::rand_float>;
		table[FxCode::RANDOM_MERSENNE_0] = as_build_in<stdlib::mersenne_0>;
		table[FxCode::RANDOM_MERSENNE_1] = as_build_in<stdlib::mersenne_1>;

		//functional
		table[FxCode::FX_ARITY]          = as_build_in<stdlib::function_arity>;
		table[FxCode::FX_INVOKE]         = as_build_in<stdlib::function_call>;
		table[FxCode::FX_IS_VARIADIC]    = as_build_in<stdlib::function_is_variadic>;

		//io
		table[FxCode::IO_RESET_COLOR]    = as_build_in<stdlib::reset_color>;
		table[FxCode::IO_SET_FG_COLOR]   = as_build_in<stdlib::set_fg_color>;
		table[FxCode::IO_SET_BG_COLOR]   = as_build_in<stdlib::set_bg_color>;
		table[FxCode::IO_IS_EOF]         = as_build_in<stdlib::is_eof>;
		table[FxCode::IO_CLOSE_STREAM]   = as_build_in<stdlib::close_stream>;
		table[FxCode::IO_PRINT]          = as_build_in<stdlib::print>;
		table[FxCode::IO_READ_STR]       = as_build_in<stdlib::read_str>;
		table[FxCode::IO_READ_LINE]      = as_build_in<stdlib::read_line>;
		table[FxCode::IO_READ_BOOL]      = as_build_in<stdlib::read_bool>;
		table[FxCode::IO_READ_CHAR]      = as_build_in<stdlib::read_char>;
		table[FxCode::IO_READ_INT]       = as_build_in<stdlib::read_int>;
		table[FxCode::IO_READ_FLOAT]     = as_build_in<stdlib::read_float>;
		table[FxCode::IO_READ_ALL]       = as_build_in<stdlib::read_all>;
		table[FxCode::IO_COUT]           = as_build_in<stdlib::cout>;
		table[FxCode::IO_FOUT]           = as_build_in<stdlib::fout>;
		table[FxCode::IO_STROUT]         = as_build_in<stdlib::strout>;
		table[FxCode::IO_CIN]            = as_build_in<stdlib::cin>;
		table[FxCode::IO_FIN]            = as_build_in<stdlib::fin>;
		table[FxCode::IO_STRIN]          = as_build_in<stdlib::strin>;

		// Json
		table[FxCode::JSON_PARSE]        = as_build_in<stdlib::json_parse>;
		table[FxCode::JSON_PRINT]        = as_build_in<stdlib::json_print>;

		// string
		table[FxCode::STR]               = as_build_in<stdlib::str>;
		table[FxCode::SPLIT_STRING]      = as_build_in<stdlib::string_split>;
		table[FxCode::CHR]               = as_build_in<stdlib::chr>;
		table[FxCode::ORD]               = as_build_in<stdlib::ord>;

		// Math
		table[FxCode::MIN]               = as_build_in<stdlib::min>;
		table[FxCode::MAX]               = as_build_in<stdlib::max>;
		table[FxCode::CLAMP]             = as_build_in<stdlib::clamp>;
		table[FxCode::ROUND]             = as_build_in<stdlib::round>;
		table[FxCode::FLOOR]             = as_build_in<stdlib::floor>;
		table[FxCode::CEIL]              = as_build_in<stdlib::ceil>;
		table[FxCode::ABS]               = as_build_in<stdlib::abs>;
		table[FxCode::SIN]               = as_build_in<stdlib::sin>;
		table[FxCode::COS]               = as_build_in<stdlib::cos>;
		table[FxCode::TAN]               = as_build_in<stdlib::tan>;
		table[FxCode::SQRT]              = as_build_in<stdlib::sqrt>;
		table[FxCode::HYPOT]             = as_build_in<stdlib::hypot>;
		table[FxCode::LOG]               = as_build_in<stdlib::log>;
		table[FxCode::LN]                = as_build_in<stdlib::ln>;
		table[FxCode::LD]                = as_build_in<stdlib::ld>;
		table[FxCode::LG]                = as_build_in<stdlib::lg>;

		// Type
		table[FxCode::TYPE_ID]           = as_build_in<stdlib::id>;
		table[FxCode::TYPE_CLONE]        = as_build_in<stdlib::clone>;
		table[FxCode::TYPE_IS]           = as_build_in<stdlib::is>;
		table[FxCode::TYPE_CAST]         = as_build_in<stdlib::cast>;
		table[FxCode::TYPE_QUEUE]        = as_build_in<stdlib::queue_new>;
		table[FxCode::TYPE_STACK]        = as_build_in<stdlib::stack_new>;
		table[FxCode::TYPE_MAP]          = as_build_in<stdlib::map_new>;

		// Iter
		table[FxCode::ITER_RANGE]        = as_build_in<stdlib::iter_range>;
		table[FxCode::ITER_NEXT]         = as_build_in<stdlib::iter_next>;
		table[FxCode::ITER_GET]          = as_build_in<stdlib::iter_get>;
		table[FxCode::ITER_MOVE]         = as_build_in<stdlib::iter_move>;
		table[FxCode::ITER_ITER]         = as_build_in<stdlib::iter_iter>;
		table[FxCode::ITER_IS_STOP]      = as_build_in<stdlib::iter_is_stop>;
		table[FxCode::ITER_COMBINED]     = as_build_in<stdlib::iter_combined>;
		table[FxCode::ITER_REVERSED]     = as_build_in<stdlib::iter_reversed>;

		// Chrono
		table[FxCode::CHRONO_CLOCK]      = as_build_in<stdlib::clock>;
		table[FxCode::CHRONO_TO_SECONDS] = as_build_in<stdlib::to_seconds>;
		table[FxCode::CHRONO_TO_MILLI_SECONDS] = as_build_in<stdlib::to_milliseconds>;

		// Container
		table[FxCode::INSERT]            = as_build_in<stdlib::insert>;
		table[FxCode::INSERT_FRONT]      = as_build_in<stdlib::insert_front>;
		table[FxCode::INSERT_BACK]       = as_build_in<stdlib::insert_back>;
		table[FxCode::REMOVE]            = as_build_in<stdlib::erase>;
		table[FxCode::REMOVE_FRONT]      = as_build_in<stdlib::erase_front>;
		table[FxCode::REMOVE_BACK]       = as_build_in<stdlib::erase_back>;
		table[FxCode::PUSH]              = as_build_in<stdlib::push>;
		table[FxCode::POP]               = as_build_in<stdlib::pop>;
		table[FxCode::PEEK]              = as_build_in<stdlib::peek>;
		table[FxCode::HAS]               = as_build_in<stdlib::has>;
		table[FxCode::SIZE]              = as_build_in<stdlib::size>;
		table[FxCode::EMPTY]             = as_build_in<stdlib::is_empty>;
		table[FxCode::AT]                = as_build_in<stdlib::at>;
		table[FxCode::FRONT]             = as_build_in<stdlib::front>;
		table[FxCode::BACK]              = as_build_in<stdlib::back>;

		// Plugin
		table[FxCode::LOAD_PLUGIN]       = as_build_in<stdlib::load_plugin>;
		table[FxCode::CALL_STACK_DEPTH]  = as_build_in<stdlib::call_stack_depth>;
		
		return table.array;
	}


	void build_in(VMCore & core) {
		static constexpr auto build_in_table = make_build_in_table();
		const auto byte0 = static_cast<std::uint32_t>(core.fetch_byte());
		const auto byte1 = static_cast<std::uint32_t>(core.fetch_byte());
		const auto code = (byte0 << 8) + byte1;
		const Value result = build_in_table[code](core);
		core.stack.push(result);
	}
}
