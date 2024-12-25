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
		sources.push_back(StringSource{"std_algorithm",  ltn::stdlib::algorithm});
		sources.push_back(StringSource{"std_bits",       ltn::stdlib::bits});
		sources.push_back(StringSource{"std_chrono",     ltn::stdlib::chrono});
		sources.push_back(StringSource{"std_container",  ltn::stdlib::container});
		sources.push_back(StringSource{"std_functional", ltn::stdlib::functional});
		sources.push_back(StringSource{"std_io",         ltn::stdlib::io});
		sources.push_back(StringSource{"std_iter",       ltn::stdlib::iter});
		sources.push_back(StringSource{"std_json",       ltn::stdlib::json});
		sources.push_back(StringSource{"std_math",       ltn::stdlib::math});
		sources.push_back(StringSource{"std_random",     ltn::stdlib::random});
		sources.push_back(StringSource{"std_string",     ltn::stdlib::string});
		sources.push_back(StringSource{"std_type",       ltn::stdlib::type});
	}
}