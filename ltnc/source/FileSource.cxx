#include "FileSource.hxx"
#include <fstream>
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	FileSource::FileSource(std::filesystem::path path) 
		: path { std::move(path) } {

		if(!std::filesystem::exists(this->path)) {
			std::ostringstream oss;
			oss 
				<< "File does not exists: "
				<< std::filesystem::relative(this->path);
			throw CompilerError{oss.str()};
		}

		if(!std::filesystem::is_regular_file(this->path)) {
			std::ostringstream oss;
			oss 
				<< "Not a file: "
				<< std::filesystem::relative(this->path);
			throw CompilerError{oss.str()};
		}
	}



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