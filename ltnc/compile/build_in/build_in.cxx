#include "build_in.hxx"
#include <unordered_map>
#include "ltnc_core/CompilerError.hxx"
#include "./algorithm.hxx"
#include "./cast.hxx"
#include "./chrono.hxx"
#include "./container.hxx"
#include "./debug.hxx"
#include "./functional.hxx"
#include "./io.hxx"
#include "./math.hxx"
#include "./newobj.hxx"
#include "./random.hxx"
#include "./type.hxx"

namespace ltn::c::compile {
	using Table = std::unordered_map<
		std::string_view,
		std::span<const std::string_view>>;


	const Table table{
		{"cast_bool",                build_in::cast_bool},
		{"cast_char",                build_in::cast_char},
		{"cast_int",                 build_in::cast_int},
		{"cast_float",               build_in::cast_float},
		{"cast_string",              build_in::cast_string},
		{"cast_array",               build_in::cast_array},

		{"algorithm_sort_ascn",      build_in::algorithm_sort_ascn},
		{"algorithm_sort_desc",      build_in::algorithm_sort_desc},
		{"algorithm_is_sorted_ascn", build_in::algorithm_is_sorted_ascn},
		{"algorithm_is_sorted_desc", build_in::algorithm_is_sorted_desc},
		{"algorithm_find",           build_in::algorithm_find},
		{"algorithm_copy_front",     build_in::algorithm_copy_front},
		{"algorithm_copy_back",      build_in::algorithm_copy_back},
		{"algorithm_fill",           build_in::algorithm_fill},
		{"algorithm_reverse",        build_in::algorithm_reverse},

		{"chrono_clock",             build_in::chrono_clock},
		{"chrono_to_seconds",        build_in::chrono_to_seconds},
		{"chrono_to_milliseconds",   build_in::chrono_to_milliseconds},

		{"queue",                    build_in::queue},
		{"stack",                    build_in::stack},
		{"map",                      build_in::map},
		{"array",                    build_in::array},
		{"range",                    build_in::range},
		{"struct",                   build_in::struc1},

		{"container_push",           build_in::container_push},
		{"container_pop",            build_in::container_pop},
		{"container_peek",           build_in::container_peek},
		{"container_contains",       build_in::container_contains},
		{"container_size",           build_in::container_size},
		{"container_empty",          build_in::container_empty},
		{"container_at",             build_in::container_at},
		{"container_front",          build_in::container_front},
		{"container_back",           build_in::container_back},
		{"container_begin",          build_in::container_begin},
		{"container_end",            build_in::container_end},
		{"container_insert_back",    build_in::container_insert_back},
		{"container_insert_front",   build_in::container_insert_front},
		{"container_insert",         build_in::container_insert},
		{"container_remove_back",    build_in::container_remove_back},
		{"container_remove_front",   build_in::container_remove_front},
		{"container_remove",         build_in::container_remove},

		{"debug_state",              build_in::debug_state},

		{"functional_invoke_1",      build_in::functional_invoke_1},
		{"functional_invoke_2",      build_in::functional_invoke_2},
		{"functional_external",      build_in::functional_external},

		{"io_cout",                  build_in::io_cout},
		{"io_fout",                  build_in::io_fout},
		{"io_strout",                build_in::io_strout},
		{"io_fg_color",              build_in::io_fg_color},
		{"io_bg_color",              build_in::io_bg_color},
		{"io_reset_color",           build_in::io_reset_color},
		{"io_print",                 build_in::io_print},
		{"io_cin",                   build_in::io_cin},
		{"io_fin",                   build_in::io_fin},
		{"io_strin",                 build_in::io_strin},
		{"io_read",                  build_in::io_read},
		{"io_read_str",              build_in::io_read_str},
		{"io_readln",                build_in::io_readln},
		{"io_read_bool",             build_in::io_read_bool},
		{"io_read_char",             build_in::io_read_char},
		{"io_read_int",              build_in::io_read_int},
		{"io_read_float",            build_in::io_read_float},
		{"io_read_all",              build_in::io_read_all},
		{"io_is_eof",                build_in::io_is_eof},
		{"io_is_good",               build_in::io_is_good},
		
		{"math_min",                 build_in::math_min},
		{"math_max",                 build_in::math_max},
		{"math_clamp",               build_in::math_clamp},
		{"math_round",               build_in::math_round},
		{"math_floor",               build_in::math_floor},
		{"math_ceil",                build_in::math_ceil},
		{"math_abs",                 build_in::math_abs},
		{"math_hypot",               build_in::math_hypot},
		{"math_sqrt",                build_in::math_sqrt},
		{"math_log",                 build_in::math_log},
		{"math_ld",                  build_in::math_ld},
		{"math_lg",                  build_in::math_lg},
		{"math_ln",                  build_in::math_ln},
		{"math_pow",                 build_in::math_pow},
		{"math_sin",                 build_in::math_sin},
		{"math_cos",                 build_in::math_cos},
		{"math_tan",                 build_in::math_tan},

		{"random_mersenne_0",        build_in::random_mersenne_0},
		{"random_mersenne_1",        build_in::random_mersenne_1},
		{"random_rand",              build_in::random_rand},
		{"random_rand_int",          build_in::random_rand_int},
		{"random_rand_float",        build_in::random_rand_float},
		{"random_split",             build_in::random_split},

		{"type_clone",               build_in::type_clone},
		{"type_typeid",              build_in::type_typeid},
	};
	
	std::span<const std::string_view> resolve_build_in(const std::string_view & key) {
		if(!table.contains(key)) {
			throw CompilerError{"Unknown build in: " + std::string(key)};
		}
		return table.at(key);
	}
}