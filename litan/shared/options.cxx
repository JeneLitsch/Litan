#include "options.hxx"
#include <algorithm>

std::span<const std::string_view> cut_options(std::span<const std::string_view> args) {
	const auto begin = std::begin(args);
	const auto end = std::end(args);
	const auto is_not_option = [] (std::string_view str) { return !str.starts_with('-'); };
	const auto first_non_option = std::find_if(begin, end, is_not_option);

	return args.subspan(0, std::distance(begin, first_non_option));
}



template<typename Options>
bool read_disable_optimization_option(Options & options, const std::string_view flag) {
	if(flag == "--no-optimization") {
		options.optimize = false;
		return true;
	}
	else {
		return false;
	}
}


template<typename Options>
bool read_help_option(Options & options, const std::string_view flag) {
	if(flag == "--help") {
		options.help = true;
		return true;
	}
	else {
		return false;
	}
}



bool read_build_option(BuildOptions & options, const std::string_view flag) {
	return
		read_compile_option(options.compilation, flag) |
		read_analysis_option(options.analysis, flag) |
		read_help_option(options, flag);
}



bool read_run_option(RunOptions & options, const std::string_view flag) {
	return 
		read_build_option(options.build, flag) |
		read_exec_option(options.exec, flag) |
		read_help_option(options, flag);
}



bool read_dump_option(DumpOptions & options, const std::string_view flag) {
	return
		read_build_option(options.build, flag) |
		read_help_option(options, flag);
}



bool read_exec_option(ExecOptions & options, const std::string_view flag) {
	return read_help_option(options, flag);
}



bool read_analysis_option(ltn::c::AnalysisOptions & options, const std::string_view flag) {
	return read_disable_optimization_option(options, flag);
}


bool read_compile_option(ltn::c::CompileOptions & options, const std::string_view flag) {
	return read_disable_optimization_option(options, flag);
}