#include "build_in.hxx"
#include <unordered_map>
#include "ltnc/CompilerError.hxx"
using namespace std::string_view_literals;

namespace ltn::c {
	using namespace ltn::inst;
	
	using Table = std::unordered_map<
		std::string_view,
		std::span<const Instruction>>;

	template<typename Inst, auto ... args>
	const std::array<Instruction, 2> single_return {
		Inst{args...}, 
		Return{},
	};

	template<typename Inst, auto ... args>
	const std::array<Instruction, 1> single {
		Inst{args...}, 
	};

	template<std::size_t CODE>
	const std::array<Instruction, 2> vm_build_in = single_return<BuildIn, CODE>;

	namespace build_in {
		const auto container_empty = std::to_array<Instruction>({
			Size{},
			Not{},
			Return{},
		});

		const auto chrono_to_milliseconds = std::to_array<Instruction>({
			CastFloat{},
			Newf{1000.0},
			Mlt{},
			Return{},
		});

		const auto functional_invoke_1 = std::to_array<Instruction>({
			Newarr{0},
			Invoke{},
			Return{},
		});

		const auto math_clamp = std::to_array<Instruction>({
			Makevar{},
			Write0{},
			Max{},
			Read0{},
			Min{},
			Return{},
		});

		const auto math_ld = std::to_array<Instruction>({
			Newf{2.0},
			Log{},
			Return{},
		});
		
		const auto math_lg = std::to_array<Instruction>({
			Newf{10.0},
			Log{},
			Return{},
		});
	}

	const Table table{
		{"cast_bool",                single_return<CastBool>},
		{"cast_char",                single_return<CastChar>},
		{"cast_int",                 single_return<CastInt>},
		{"cast_float",               single_return<CastFloat>},
		{"cast_string",              single_return<CastString>},
		{"cast_array",               single_return<CastArray>},

		{"algorithm_sort_ascn",      vm_build_in<0x00>},
		{"algorithm_sort_desc",      vm_build_in<0x01>},
		{"algorithm_is_sorted_ascn", vm_build_in<0x02>},
		{"algorithm_is_sorted_desc", vm_build_in<0x03>},
		{"algorithm_find",           vm_build_in<0x04>},
		{"algorithm_copy_front",     vm_build_in<0x05>},
		{"algorithm_copy_back",      vm_build_in<0x06>},
		{"algorithm_fill",           vm_build_in<0x07>},
		{"algorithm_reverse",        vm_build_in<0x08>},

		{"chrono_clock",             single_return<Newclock>},
		{"chrono_to_seconds",        single_return<CastFloat>},
		{"chrono_to_milliseconds",   build_in::chrono_to_milliseconds},

		{"queue",                    single_return<Newqueue>},
		{"stack",                    single_return<Newstack>},
		{"map",                      single_return<Newmap>},
		{"array",                    single_return<Newarr, 0>},
		{"range",                    single_return<Newrange>},
		{"struct",                   single_return<Newstruct>},

		{"container_push",           single<Push>},
		{"container_pop",            single_return<Pop>},
		{"container_peek",           single_return<Peek>},
		{"container_contains",       single_return<Contains>},
		{"container_size",           single_return<Size>},
		{"container_empty",          build_in::container_empty},
		{"container_at",             single_return<At>},
		{"container_front",          single_return<Front>},
		{"container_back",           single_return<Back>},
		{"container_begin",          single_return<Begin>},
		{"container_end",            single_return<End>},
		{"container_insert_back",    single<Insert, 0x02>},
		{"container_insert_front",   single<Insert, 0x00>},
		{"container_insert",         single<Insert, 0x01>},
		{"container_remove_back",    single<Remove, 0x02>},
		{"container_remove_front",   single<Remove, 0x00>},
		{"container_remove",         single<Remove, 0x01>},

		{"debug_state",              single_return<State>},

		{"functional_invoke_1",      build_in::functional_invoke_1},
		{"functional_invoke_2",      single_return<Invoke>},
		{"functional_external",      single_return<External>},
		{"functional_arity",         vm_build_in<0x20>},

		{"io_cout",                  single_return<Newout, 0x00>},
		{"io_fout",                  single_return<Newout, 0x01>},
		{"io_strout",                single_return<Newout, 0x02>},
		{"io_fg_color",              single<Stylize, 0x00>},
		{"io_bg_color",              single<Stylize, 0x01>},
		{"io_reset_color",           single<Stylize, 0x02>},
		{"io_print",                 single<Out>},
		{"io_cin",                   single_return<Newin, 0x00>},
		{"io_fin",                   single_return<Newin, 0x01>},
		{"io_strin",                 single_return<Newin, 0x02>},
		{"io_read",                  single_return<InStr>},
		{"io_read_str",              single_return<InStr>},
		{"io_readln",                single_return<InLine>},
		{"io_read_bool",             single_return<InBool>},
		{"io_read_char",             single_return<InChar>},
		{"io_read_int",              single_return<InInt>},
		{"io_read_float",            single_return<InFloat>},
		{"io_read_all",              single_return<InAll>},
		{"io_is_eof",                single_return<IsEof>},
		{"io_is_good",               single_return<IsGood>},
		{"io_close",                 single_return<CloseStream>},
		
		{"math_min",                 single_return<Min>},
		{"math_max",                 single_return<Max>},
		{"math_clamp",               build_in::math_clamp},
		{"math_round",               single_return<Round>},
		{"math_floor",               single_return<Floor>},
		{"math_ceil",                single_return<Ceil>},
		{"math_abs",                 single_return<Abs>},
		{"math_hypot",               single_return<Hypot>},
		{"math_sqrt",                single_return<Sqrt>},
		{"math_log",                 single_return<Log>},
		{"math_ld",                  build_in::math_ld},
		{"math_lg",                  build_in::math_lg},
		{"math_ln",                  single_return<Ln>},
		{"math_pow",                 single_return<Pow>},
		{"math_sin",                 single_return<Sin>},
		{"math_cos",                 single_return<Cos>},
		{"math_tan",                 single_return<Tan>},

		{"random_mersenne_0",        single_return<Newrng, 0x00>},
		{"random_mersenne_1",        single_return<Newrng, 0x01>},
		{"random_split",             vm_build_in<0x10>},
		{"random_rand",              vm_build_in<0x11>},
		{"random_rand_int",          vm_build_in<0x12>},
		{"random_rand_float",        vm_build_in<0x13>},

		{"type_clone",               single_return<Clone>},
		{"type_typeid",              single_return<TypeId>},
	};
	
	std::span<const Instruction> resolve_build_in(const std::string_view & key) {
		if(!table.contains(key)) {
			throw CompilerError{"Unknown build in: " + std::string(key)};
		}
		return table.at(key);
	}
}