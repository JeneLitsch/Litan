#include "file.hxx"


std::ofstream open_file(const std::filesystem::path & path, std::ios::openmode openmode) {
	const auto dir = path.parent_path();
	if(!std::filesystem::exists(dir) && !std::filesystem::create_directory(dir)) {
		std::ostringstream oss;
		oss << "Directory " << dir << " does not exist and cannot be created.";
		throw std::runtime_error { oss.str() };
	}

	std::ofstream ofile { path, openmode };
	if(!ofile) {
		std::ostringstream oss;
		oss << "Cannot open target " << path; 
		throw std::runtime_error { oss.str() };
	}

	return ofile;
}
