#include "Args.hxx"
#include "ltnc/CompilerError.hxx"
ltn::c::Args::Args(const char ** argv, std::size_t argc) {
	std::span<const char*> args(argv, argc);
	bool first = true;
	for(const std::string_view arg : args) {
		if(first) {
			first = false;
		}
		else {
			if(arg.starts_with("-")) {
				this->flags.insert(std::string(arg));
			}
			this->files.push_back(arg);
		}
	}
	if(this->files.size() < 2) {
		throw CompilerError{"Source and traget needed", 0};
	}
}

const std::span<const std::filesystem::path> ltn::c::Args::getSources() const {
	return { this->files.begin() + 2, this->files.end() };
}

const std::filesystem::path & ltn::c::Args::getStdLib() const {
	return this->files[1];
}

const std::filesystem::path & ltn::c::Args::getTarget() const {
	return this->files[0];
}

bool ltn::c::Args::isSet(const std::string & flag) const {
	return this->flags.contains(flag);
}
