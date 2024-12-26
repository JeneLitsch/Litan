#pragma once
#include <span>
#include <string_view>
#include "litan_compiler/Ltnc.hxx"

struct BuildOptions {
	ltn::c::AnalysisOptions analysis;
	ltn::c::CompileOptions compilation;
};

struct ExecOptions {

};

struct RunOptions {
	BuildOptions build;
	ExecOptions exec;
};

struct DumpOptions {
	BuildOptions build;
};




std::span<const std::string_view> cut_options(std::span<const std::string_view> args);




bool read_analysis_option(ltn::c::AnalysisOptions & options, const std::string_view flag);
bool read_compile_option(ltn::c::CompileOptions & options, const std::string_view flag);
bool read_build_option(BuildOptions & options, const std::string_view flag);
bool read_run_option(RunOptions & options, const std::string_view flag);
bool read_dump_option(DumpOptions & options, const std::string_view flag);
bool read_exec_option(ExecOptions & options, const std::string_view flag);

template<typename Options, auto read>
Options parse_options(std::span<const std::string_view> flags) {
	Options options;
	for (std::string_view flag : flags) {
		if(!read(options, flag)) {
			std::cout << "[Warning] Unknown option flag: " << flag << "\n";
		}
	}
	return options;
}