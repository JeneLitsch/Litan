#include "read_sources.hxx"
#include "ltnc/source/FileSource.hxx"
#include "ltnc/source/StringSource.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/stdlib/algorithm.hxx"
#include "ltnc/stdlib/bits.hxx"
#include "ltnc/stdlib/cast.hxx"
#include "ltnc/stdlib/chrono.hxx"
#include "ltnc/stdlib/container.hxx"
#include "ltnc/stdlib/debug.hxx"
#include "ltnc/stdlib/functional.hxx"
#include "ltnc/stdlib/io.hxx"
#include "ltnc/stdlib/iter.hxx"
#include "ltnc/stdlib/json.hxx"
#include "ltnc/stdlib/math.hxx"
#include "ltnc/stdlib/random.hxx"
#include "ltnc/stdlib/range.hxx"
#include "ltnc/stdlib/type.hxx"
#include "ltnc/stdlib/string.hxx"

namespace ltn::c {
	namespace {
		std::vector<ltn::c::Source> read_source_impl(
			const auto & filepaths,
			ltn::c::Reporter & reporter) {


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
					reporter << ltn::c::CompilerError { oss.str() };
				}
			}
			return sources;
		}
	}




	std::vector<ltn::c::Source> read_sources(
		const std::vector<std::filesystem::path> & filepaths,
		ltn::c::Reporter & reporter) {
		return read_source_impl(filepaths, reporter);
	}



	std::vector<ltn::c::Source> read_sources(
		const std::vector<std::string> & filepaths,
		ltn::c::Reporter & reporter) {
		return read_source_impl(filepaths, reporter);
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