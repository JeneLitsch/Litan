#include "build_in.hxx"
#include <unordered_map>
#include "ltnc/CompilerError.hxx"
#include "ltn/fxcodes.hxx"
using namespace std::string_view_literals;

namespace ltn::c {
	using Table = std::unordered_map<
		std::string_view,
		std::span<const inst::Inst>>;



	template<auto inst_fx, auto ... args>
	const std::array<inst::Inst, 2> single_return {
		inst_fx(args...), 
		inst::retvrn(),
	};



	template<auto inst_fx, auto ... args>
	const std::array<inst::Inst, 1> single {
		inst_fx(args...), 
	};



	template<ltn::FxCode CODE>
	const std::array<inst::Inst, 2> vm_build_in = single_return<inst::build_in, static_cast<std::size_t>(CODE)>;



	namespace build_in {
		const auto chrono_to_milliseconds = std::to_array<inst::Inst>({
			inst::cast_float(),
			inst::newf(1000.0),
			inst::mlt(),
			inst::retvrn(),
		});
	}



	const Table table{
		{"algorithm_sort_ascn",      vm_build_in<FxCode::SORT_ASCN>},
		{"algorithm_sort_desc",      vm_build_in<FxCode::SORT_DESC>},
		{"algorithm_is_sorted_ascn", vm_build_in<FxCode::IS_SORTED_ASCN>},
		{"algorithm_is_sorted_desc", vm_build_in<FxCode::IS_SORTED_DESC>},
		{"algorithm_find",           vm_build_in<FxCode::FIND>},
		{"algorithm_fill",           vm_build_in<FxCode::FILL>},
		{"algorithm_reverse",        vm_build_in<FxCode::REVERSE>},

		{"chrono_clock",             vm_build_in<FxCode::CHRONO_CLOCK>},
		{"chrono_to_seconds",        vm_build_in<FxCode::CHRONO_TO_SECONDS>},
		{"chrono_to_milliseconds",   vm_build_in<FxCode::CHRONO_TO_MILLI_SECONDS>},

		{"queue",                    vm_build_in<FxCode::TYPE_QUEUE>},
		{"stack",                    vm_build_in<FxCode::TYPE_STACK>},
		{"map",                      vm_build_in<FxCode::TYPE_MAP>},
		{"struct",                   vm_build_in<FxCode::TYPE_STRUCT>},

		{"container_push",           vm_build_in<FxCode::PUSH>},
		{"container_pop",            vm_build_in<FxCode::POP>},
		{"container_peek",           vm_build_in<FxCode::PEEK>},
		{"container_contains",       vm_build_in<FxCode::CONTAINS>},
		{"container_size",           vm_build_in<FxCode::SIZE>},
		{"container_empty",          vm_build_in<FxCode::EMPTY>},
		{"container_at",             vm_build_in<FxCode::AT>},
		{"container_front",          vm_build_in<FxCode::FRONT>},
		{"container_back",           vm_build_in<FxCode::BACK>},
		{"container_insert_front",   vm_build_in<FxCode::INSERT_FRONT>},
		{"container_insert_back",    vm_build_in<FxCode::INSERT_BACK>},
		{"container_insert",         vm_build_in<FxCode::INSERT>},
		{"container_remove_front",   vm_build_in<FxCode::REMOVE_FRONT>},
		{"container_remove_back",    vm_build_in<FxCode::REMOVE_BACK>},
		{"container_remove",         vm_build_in<FxCode::REMOVE>},

		{"functional_invoke_2",      vm_build_in<FxCode::INVOKE>},
		{"functional_arity",         vm_build_in<FxCode::ARITY>},

		{"io_cout",                  vm_build_in<FxCode::IO_COUT>},
		{"io_fout",                  vm_build_in<FxCode::IO_FOUT>},
		{"io_strout",                vm_build_in<FxCode::IO_STROUT>},
		{"io_cin",                   vm_build_in<FxCode::IO_CIN>},
		{"io_fin",                   vm_build_in<FxCode::IO_FIN>},
		{"io_strin",                 vm_build_in<FxCode::IO_STRIN>},
		{"io_reset_color",           vm_build_in<FxCode::IO_RESET_COLOR>},
		{"io_fg_color",              vm_build_in<FxCode::IO_SET_FG_COLOR>},
		{"io_bg_color",              vm_build_in<FxCode::IO_SET_BG_COLOR>},
		{"io_print",                 vm_build_in<FxCode::IO_PRINT>},
		{"io_read",                  vm_build_in<FxCode::IO_READ_STR>},
		{"io_read_str",              vm_build_in<FxCode::IO_READ_STR>},
		{"io_readln",                vm_build_in<FxCode::IO_READ_LINE>},
		{"io_read_bool",             vm_build_in<FxCode::IO_READ_BOOL>},
		{"io_read_char",             vm_build_in<FxCode::IO_READ_CHAR>},
		{"io_read_int",              vm_build_in<FxCode::IO_READ_INT>},
		{"io_read_float",            vm_build_in<FxCode::IO_READ_FLOAT>},
		{"io_read_all",              vm_build_in<FxCode::IO_READ_ALL>},
		{"io_close",                 vm_build_in<FxCode::IO_CLOSE_STREAM>},
		{"io_is_eof",                vm_build_in<FxCode::IO_IS_EOF>},
		
		{"math_min",                 vm_build_in<FxCode::MIN>},
		{"math_max",                 vm_build_in<FxCode::MAX>},
		{"math_clamp",               vm_build_in<FxCode::CLAMP>},
		{"math_round",               vm_build_in<FxCode::ROUND>},
		{"math_floor",               vm_build_in<FxCode::FLOOR>},
		{"math_ceil",                vm_build_in<FxCode::CEIL>},
		{"math_abs",                 vm_build_in<FxCode::ABS>},
		{"math_hypot",               vm_build_in<FxCode::HYPOT>},
		{"math_sqrt",                vm_build_in<FxCode::SQRT>},
		{"math_log",                 vm_build_in<FxCode::LOG>},
		{"math_ld",                  vm_build_in<FxCode::LD>},
		{"math_lg",                  vm_build_in<FxCode::LG>},
		{"math_ln",                  vm_build_in<FxCode::LN>},
		{"math_sin",                 vm_build_in<FxCode::SIN>},
		{"math_cos",                 vm_build_in<FxCode::COS>},
		{"math_tan",                 vm_build_in<FxCode::TAN>},

		{"random_mersenne_0",        vm_build_in<FxCode::RANDOM_MERSENNE_0>},
		{"random_mersenne_1",        vm_build_in<FxCode::RANDOM_MERSENNE_1>},
		{"random_split",             vm_build_in<FxCode::RANDOM_SPLIT>},
		{"random_rand",              vm_build_in<FxCode::RANDOM_RAND>},
		{"random_rand_int",          vm_build_in<FxCode::RANDOM_RAND_INT>},
		{"random_rand_float",        vm_build_in<FxCode::RANDOM_RAND_FLOAT>},

		{"type_clone",               vm_build_in<FxCode::TYPE_CLONE>},
		{"type_typeid",              vm_build_in<FxCode::TYPE_ID>},
		{"type_is",                  vm_build_in<FxCode::TYPE_IS>},
		{"type_cast",                vm_build_in<FxCode::TYPE_CAST>},

		{"to_string",                vm_build_in<FxCode::TO_STRING>},
		{"split_string",             vm_build_in<FxCode::SPLIT_STRING>},
		{"join_string",              vm_build_in<FxCode::JOIN_STRING>},

		{"iter_range",               vm_build_in<FxCode::ITER_RANGE>},
		{"iter_next",                vm_build_in<FxCode::ITER_NEXT>},
		{"iter_get",                 vm_build_in<FxCode::ITER_GET>},
		{"iter_move",                vm_build_in<FxCode::ITER_MOVE>},
		{"iter_iter",                vm_build_in<FxCode::ITER_ITER>},
		{"iter_is_stop",             vm_build_in<FxCode::ITER_IS_STOP>},
	};
	


	std::span<const inst::Inst> resolve_build_in(const std::string_view & key) {
		if(!table.contains(key)) {
			throw CompilerError{"Unknown build in: " + std::string(key)};
		}
		return table.at(key);
	}
}