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

		{"chrono_clock",             single_return<inst::newclock>},
		{"chrono_to_seconds",        single_return<inst::cast_float>},
		{"chrono_to_milliseconds",   build_in::chrono_to_milliseconds},

		{"queue",                    single_return<inst::newqueue>},
		{"stack",                    single_return<inst::newstack>},
		{"map",                      single_return<inst::newmap>},
		{"struct",                   single_return<inst::newstruct>},

		{"container_push",           single<inst::push>},
		{"container_pop",            single_return<inst::pop>},
		{"container_peek",           single_return<inst::peek>},
		{"container_contains",       single_return<inst::contains>},
		{"container_size",           single_return<inst::size>},
		{"container_empty",          single_return<inst::empty>},
		{"container_at",             single_return<inst::at>},
		{"container_front",          single_return<inst::front>},
		{"container_back",           single_return<inst::back>},
		{"container_insert_back",    single<inst::insert, 0x02>},
		{"container_insert_front",   single<inst::insert, 0x00>},
		{"container_insert",         single<inst::insert, 0x01>},
		{"container_remove_back",    single<inst::remove, 0x02>},
		{"container_remove_front",   single<inst::remove, 0x00>},
		{"container_remove",         single<inst::remove, 0x01>},

		{"functional_invoke_2",      single_return<inst::invoke_variadic>},
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

		{"to_string",                vm_build_in<FxCode::TO_STRING>},
		{"split_string",             vm_build_in<FxCode::SPLIT_STRING>},
		{"join_string",              vm_build_in<FxCode::JOIN_STRING>},

		{"iter_range",               vm_build_in<FxCode::ITER_RANGE>},
		{"iter_next",                vm_build_in<FxCode::ITER_NEXT>},
		{"iter_iter",                vm_build_in<FxCode::ITER_ITER>},
	};
	


	std::span<const inst::Inst> resolve_build_in(const std::string_view & key) {
		if(!table.contains(key)) {
			throw CompilerError{"Unknown build in: " + std::string(key)};
		}
		return table.at(key);
	}
}