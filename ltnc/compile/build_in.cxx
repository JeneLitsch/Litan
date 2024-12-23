#include "build_in.hxx"
#include <unordered_map>
#include "ltnc/CompilerError.hxx"
#include "ltn/fxcodes.hxx"
using namespace std::string_view_literals;

namespace ltn::c {
	const std::unordered_map<std::string_view, FxCode> table{
		{"algorithm_sort_ascn",      FxCode::SORT_ASCN},
		{"algorithm_sort_desc",      FxCode::SORT_DESC},
		{"algorithm_is_sorted_ascn", FxCode::IS_SORTED_ASCN},
		{"algorithm_is_sorted_desc", FxCode::IS_SORTED_DESC},
		{"algorithm_find",           FxCode::FIND},
		{"algorithm_fill",           FxCode::FILL},
		{"algorithm_reverse",        FxCode::REVERSE},
		{"algorithm_reduce_l_2",     FxCode::ALGORITHM_REDUCE_L_2},
		{"algorithm_reduce_l_3",     FxCode::ALGORITHM_REDUCE_L_3},

		{"chrono_clock",             FxCode::CHRONO_CLOCK},
		{"chrono_to_seconds",        FxCode::CHRONO_TO_SECONDS},
		{"chrono_to_milliseconds",   FxCode::CHRONO_TO_MILLI_SECONDS},

		{"queue",                    FxCode::TYPE_QUEUE},
		{"stack",                    FxCode::TYPE_STACK},
		{"map",                      FxCode::TYPE_MAP},

		{"container_push",           FxCode::PUSH},
		{"container_pop",            FxCode::POP},
		{"container_peek",           FxCode::PEEK},
		{"container_contains",       FxCode::CONTAINS},
		{"container_size",           FxCode::SIZE},
		{"container_empty",          FxCode::EMPTY},
		{"container_at",             FxCode::AT},
		{"container_front",          FxCode::FRONT},
		{"container_back",           FxCode::BACK},
		{"container_insert_front",   FxCode::INSERT_FRONT},
		{"container_insert_back",    FxCode::INSERT_BACK},
		{"container_insert",         FxCode::INSERT},
		{"container_remove_front",   FxCode::REMOVE_FRONT},
		{"container_remove_back",    FxCode::REMOVE_BACK},
		{"container_remove",         FxCode::REMOVE},

		{"fx_invoke",                FxCode::FX_INVOKE},
		{"fx_arity",                 FxCode::FX_ARITY},
		{"fx_is_variadic",           FxCode::FX_IS_VARIADIC},
		{"fx_noroutine",             FxCode::FX_NOROUTINE},
		{"fx_is_noroutine",          FxCode::FX_IS_NOROUTINE},

		{"io_cout",                  FxCode::IO_COUT},
		{"io_fout",                  FxCode::IO_FOUT},
		{"io_strout",                FxCode::IO_STROUT},
		{"io_cin",                   FxCode::IO_CIN},
		{"io_fin",                   FxCode::IO_FIN},
		{"io_strin",                 FxCode::IO_STRIN},
		{"io_reset_color",           FxCode::IO_RESET_COLOR},
		{"io_fg_color",              FxCode::IO_SET_FG_COLOR},
		{"io_bg_color",              FxCode::IO_SET_BG_COLOR},
		{"io_print",                 FxCode::IO_PRINT},
		{"io_read",                  FxCode::IO_READ_STR},
		{"io_read_str",              FxCode::IO_READ_STR},
		{"io_readln",                FxCode::IO_READ_LINE},
		{"io_read_bool",             FxCode::IO_READ_BOOL},
		{"io_read_char",             FxCode::IO_READ_CHAR},
		{"io_read_int",              FxCode::IO_READ_INT},
		{"io_read_float",            FxCode::IO_READ_FLOAT},
		{"io_read_all",              FxCode::IO_READ_ALL},
		{"io_close",                 FxCode::IO_CLOSE_STREAM},
		{"io_is_eof",                FxCode::IO_IS_EOF},

		{"json_parse",               FxCode::JSON_PARSE},
		{"json_print",               FxCode::JSON_PRINT},
		
		{"math_min",                 FxCode::MIN},
		{"math_max",                 FxCode::MAX},
		{"math_clamp",               FxCode::CLAMP},
		{"math_round",               FxCode::ROUND},
		{"math_floor",               FxCode::FLOOR},
		{"math_ceil",                FxCode::CEIL},
		{"math_abs",                 FxCode::ABS},
		{"math_hypot",               FxCode::HYPOT},
		{"math_sqrt",                FxCode::SQRT},
		{"math_log",                 FxCode::LOG},
		{"math_ld",                  FxCode::LD},
		{"math_lg",                  FxCode::LG},
		{"math_ln",                  FxCode::LN},
		{"math_sin",                 FxCode::SIN},
		{"math_cos",                 FxCode::COS},
		{"math_tan",                 FxCode::TAN},

		{"random_mersenne_0",        FxCode::RANDOM_MERSENNE_0},
		{"random_mersenne_1",        FxCode::RANDOM_MERSENNE_1},
		{"random_split",             FxCode::RANDOM_SPLIT},
		{"random_rand",              FxCode::RANDOM_RAND},
		{"random_rand_int",          FxCode::RANDOM_RAND_INT},
		{"random_rand_float",        FxCode::RANDOM_RAND_FLOAT},

		{"type_clone",               FxCode::TYPE_CLONE},
		{"type_typeid",              FxCode::TYPE_ID},
		{"type_is",                  FxCode::TYPE_IS},
		{"type_cast",                FxCode::TYPE_CAST},

		{"to_string",                FxCode::TO_STRING},
		{"split_string",             FxCode::SPLIT_STRING},
		{"chr",                      FxCode::CHR},
		{"ord",                      FxCode::ORD},

		{"iter_range",               FxCode::ITER_RANGE},
		{"iter_next",                FxCode::ITER_NEXT},
		{"iter_get",                 FxCode::ITER_GET},
		{"iter_move",                FxCode::ITER_MOVE},
		{"iter_iter",                FxCode::ITER_ITER},
		{"iter_is_stop",             FxCode::ITER_IS_STOP},
		{"iter_zipped",              FxCode::ITER_COMBINED},
		{"iter_reversed",            FxCode::ITER_REVERSED},

		{"load_plugin",              FxCode::LOAD_PLUGIN},
	};
	


	inst::Inst resolve_build_in(const std::string_view & key) {
		if(!table.contains(key)) {
			throw CompilerError{"Unknown build in: " + std::string(key)};
		}
		return inst::build_in(static_cast<std::uint16_t>(table.at(key)));
	}
}