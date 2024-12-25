#include "read_sources.hxx"
#include "litan_compiler/source/FileSource.hxx"
#include "litan_compiler/source/StringSource.hxx"
#include "litan_compiler/CompilerError.hxx"
#include "litan_compiler/stdlib/algorithm.hxx"
#include "litan_compiler/stdlib/bits.hxx"
#include "litan_compiler/stdlib/cast.hxx"
#include "litan_compiler/stdlib/chrono.hxx"
#include "litan_compiler/stdlib/container.hxx"
#include "litan_compiler/stdlib/debug.hxx"
#include "litan_compiler/stdlib/functional.hxx"
#include "litan_compiler/stdlib/io.hxx"
#include "litan_compiler/stdlib/iter.hxx"
#include "litan_compiler/stdlib/json.hxx"
#include "litan_compiler/stdlib/math.hxx"
#include "litan_compiler/stdlib/random.hxx"
#include "litan_compiler/stdlib/range.hxx"
#include "litan_compiler/stdlib/type.hxx"
#include "litan_compiler/stdlib/string.hxx"

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
		sources.push_back(StringSource{"std_algorithm", std_algorithm});
		sources.push_back(StringSource{"std_bits", std_bits});
		sources.push_back(StringSource{"std_cast", std_cast});
		sources.push_back(StringSource{"std_chrono", std_chrono});
		sources.push_back(StringSource{"std_container", std_container});
		sources.push_back(StringSource{"std_debug", std_debug});
		sources.push_back(StringSource{"std_functional", std_functional});
		sources.push_back(StringSource{"std_io", std_io});
		sources.push_back(StringSource{"std_iter", std_iter});
		sources.push_back(StringSource{"std_json", std_json});
		sources.push_back(StringSource{"std_math", std_math});
		sources.push_back(StringSource{"std_random", std_random});
		sources.push_back(StringSource{"std_range", std_range});
		sources.push_back(StringSource{"std_string", std_string});
		sources.push_back(StringSource{"std_type", std_type});
	}
}