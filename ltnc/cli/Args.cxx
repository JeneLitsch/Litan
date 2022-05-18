#include "Args.hxx"
#include "ltnc_core/CompilerError.hxx"
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
			else {
				this->files.push_back(arg);
			}
		}
	}
	if(this->files.size() < 2) {
		throw CompilerError{"Source and traget needed", {}};
	}
}

const std::span<const std::filesystem::path> ltn::c::Args::get_sources() const {
	return { this->files.begin() + 1, this->files.end() };
}

const std::filesystem::path & ltn::c::Args::get_target() const {
	return this->files[0];
}

bool ltn::c::Args::is_set(const std::string & flag) const {
	return this->flags.contains(flag);
}
