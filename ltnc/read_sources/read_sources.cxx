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

			std::vector<Source> sources = {
				StringSource{"std_algorithm", std_algorithm},
				StringSource{"std_bits", std_bits},
				StringSource{"std_cast", std_cast},
				StringSource{"std_chrono", std_chrono},
				StringSource{"std_container", std_container},
				StringSource{"std_debug", std_debug},
				StringSource{"std_functional", std_functional},
				StringSource{"std_io", std_io},
				StringSource{"std_math", std_math},
				StringSource{"std_random", std_random},
				StringSource{"std_range", std_range},
				StringSource{"std_string", std_string},
				StringSource{"std_type", std_type},
			};
			
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
}