#include "build_in.hxx"
#include <unordered_map>
#include "ltnc/CompilerError.hxx"
#include "build_in/algorithm.hxx"
#include "build_in/cast.hxx"
#include "build_in/chrono.hxx"
#include "build_in/container.hxx"
#include "build_in/debug.hxx"
#include "build_in/functional.hxx"
#include "build_in/io.hxx"
#include "build_in/newobj.hxx"

namespace ltn::c::compile {
	using Table = std::unordered_map<
		std::string_view,
		std::span<const std::string_view>>;

	const Table table{
		{"cast_bool",                cast_bool},
		{"cast_char",                cast_char},
		{"cast_int",                 cast_int},
		{"cast_float",               cast_float},
		{"cast_string",              cast_string},
		{"cast_array",               cast_array},

		{"algorithm_sort_ascn",      algorithm_sort_ascn},
		{"algorithm_sort_desc",      algorithm_sort_desc},
		{"algorithm_is_sorted_ascn", algorithm_is_sorted_ascn},
		{"algorithm_is_sorted_desc", algorithm_is_sorted_desc},
		{"algorithm_find",           algorithm_find},
		{"algorithm_copy_front",     algorithm_copy_front},
		{"algorithm_copy_back",      algorithm_copy_back},
		{"algorithm_fill",           algorithm_fill},
		{"algorithm_reverse",        algorithm_reverse},

		{"chrono_clock",             chrono_clock},
		{"chrono_to_seconds",        chrono_to_seconds},
		{"chrono_to_milliseconds",   chrono_to_milliseconds},

		{"queue",                    queue},
		{"stack",                    stack},
		{"map",                      map},
		{"array",                    array},

		{"container_push",           container_push},
		{"container_pop",            container_pop},
		{"container_peek",           container_peek},
		{"container_contains",       container_contains},
		{"container_size",           container_size},
		{"container_empty",          container_empty},
		{"container_at",             container_at},
		{"container_front",          container_front},
		{"container_back",           container_back},
		{"container_begin",          container_begin},
		{"container_end",            container_end},
		{"container_insert_back",    container_insert_back},
		{"container_insert_front",   container_insert_front},
		{"container_insert",         container_insert},
		{"container_remove_back",    container_remove_back},
		{"container_remove_front",   container_remove_front},
		{"container_remove",         container_remove},

		{"debug_state",              debug_state},

		{"functional_invoke_1",      functional_invoke_1},
		{"functional_invoke_2",      functional_invoke_2},
		{"functional_external",      functional_external},

		{"io_cout",                  io_cout},
		{"io_fout",                  io_fout},
		{"io_strout",                io_strout},
		{"io_print",                 io_print},
		{"io_cin",                   io_cin},
		{"io_fin",                   io_fin},
		{"io_strin",                 io_strin},
		{"io_read",                  io_read},
		{"io_read_str",              io_read_str},
		{"io_readln",                io_readln},
		{"io_read_bool",             io_read_bool},
		{"io_read_char",             io_read_char},
		{"io_read_int",              io_read_int},
		{"io_read_float",            io_read_float},
		{"io_read_all",              io_read_all},
		{"io_is_eof",                io_is_eof},
		{"io_is_good",               io_is_good},
	};
	
	std::span<const std::string_view> resolve_build_in(const std::string_view & key) {
		if(!table.contains(key)) {
			throw CompilerError{"Unknown build in: " + std::string(key)};
		}
		return table.at(key);
	}
}