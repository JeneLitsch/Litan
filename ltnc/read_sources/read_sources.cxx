#include "read_sources.hxx"
#include "ltnc/source/FileSource.hxx"
#include "ltnc/source/StringSource.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		std::vector<ltn::c::Source> read_source_impl(
			const auto & filepaths,
			ltn::c::Reporter & reporter) {
			
			std::vector<ltn::c::Source> sources;
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