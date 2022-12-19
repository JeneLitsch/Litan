#include "FileSource.hxx"
#include <fstream>

namespace ltn::c {
	FileSource::FileSource(std::filesystem::path path) 
		: path { std::move(path) } {}



	std::unique_ptr<std::istream> FileSource::make_istream() const {
		return std::make_unique<std::ifstream>(this->path);
	}



	std::string FileSource::get_name() const {
		return this->path.filename();
	}



	std::string FileSource::get_full_name() const {
		return this->path.string();
	}
	
}