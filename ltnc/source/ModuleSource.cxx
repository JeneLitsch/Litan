#include "ModuleSource.hxx"
#include <fstream>
#include "ltnc/CompilerError.hxx"
#include "FileSource.hxx"

namespace ltn::c {
	ModuleSource::ModuleSource(std::filesystem::path path) 
		: path        { std::move(path) }
		, header_path { this->path / "__module__.ltn" } {

		if(!std::filesystem::exists(this->path)) {
			std::ostringstream oss;
			oss 
				<< "Module does not exists: "
				<< std::filesystem::relative(this->path);
			throw CompilerError{oss.str()};
		}

		if(!std::filesystem::is_directory(this->path)) {
			std::ostringstream oss;
			oss 
				<< "Module is not a directory: "
				<< std::filesystem::relative(this->path);
			throw CompilerError{oss.str()};
		}

		if(!std::filesystem::exists(this->header_path)) {
			std::ostringstream oss;
			oss 
				<< "Directory does not contain __module__.ltn: "
				<< std::filesystem::relative(this->path);
			throw CompilerError{oss.str()};
		}

		if(!std::filesystem::is_regular_file(this->header_path)) {
			std::ostringstream oss;
			oss 
				<< "Directory does not contain __module__.ltn: "
				<< std::filesystem::relative(this->path);
			throw CompilerError{oss.str()};
		}
	}



	std::unique_ptr<std::istream> ModuleSource::make_istream() const {
		return std::make_unique<std::ifstream>(this->header_path);
	}



	std::string ModuleSource::get_name() const {
		return this->path.filename();
	}



	std::string ModuleSource::get_full_name() const {
		return this->path.string();
	}



	std::vector<Source> ModuleSource::get_module_subsources() const {
		std::vector<Source> sources;
		std::filesystem::directory_iterator dir {this->path};
		for(const std::filesystem::directory_entry & entry : dir) {
			if(std::filesystem::is_regular_file(entry)) {
				sources.push_back(FileSource{entry.path()});
			}
		}
 		return sources;
	}	
}