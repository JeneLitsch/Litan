#include "read_sources.hxx"
#include "litan_compiler/source/FileSource.hxx"
#include "litan_compiler/source/StringSource.hxx"
#include "litan_compiler/CompilerError.hxx"
#include "litan_stdlib/litan_stdlib.h"

namespace ltn::c {
	namespace {
		std::vector<ltn::c::Source> read_source_impl(const auto & filepaths) {

			std::vector<Source> sources;
			inject_stdlib(sources);
			for(const auto & source_path : filepaths) {
				const auto path = std::filesystem::path{source_path};
				if(std::filesystem::exists(path)) {
					sources.push_back(ltn::c::FileSource{path});
				}
				else {
					std::ostringstream oss;
					oss << "Cannot open source " << source_path;
					throw ltn::c::CompilerError { oss.str() };
				}
			}
			return sources;
		}
	}




	std::vector<ltn::c::Source> read_sources(
		const std::vector<std::filesystem::path> & filepaths) {
		return read_source_impl(filepaths);
	}



	std::vector<ltn::c::Source> read_sources(
		const std::vector<std::string> & filepaths) {
		return read_source_impl(filepaths);
	}



	void inject_stdlib(std::vector<ltn::c::Source> & sources) {
		sources.push_back(StringSource{"std_algorithm", litan_stdlib_algorithm});
		sources.push_back(StringSource{"std_bits", litan_stdlib_bits});
		sources.push_back(StringSource{"std_chrono", litan_stdlib_chrono});
		sources.push_back(StringSource{"std_container", litan_stdlib_container});
		sources.push_back(StringSource{"std_functional", litan_stdlib_functional});
		sources.push_back(StringSource{"std_io", litan_stdlib_io});
		sources.push_back(StringSource{"std_iter", litan_stdlib_iter});
		sources.push_back(StringSource{"std_json", litan_stdlib_json});
		sources.push_back(StringSource{"std_math", litan_stdlib_math});
		sources.push_back(StringSource{"std_random", litan_stdlib_random});
		sources.push_back(StringSource{"std_string", litan_stdlib_string});
		sources.push_back(StringSource{"std_type", litan_stdlib_type});
	}
}