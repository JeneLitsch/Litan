#include "Args.hxx"
#include <stdexcept>
ltn::a::Args::Args(const char ** argv, std::size_t argc) {
	std::span<const char*> args(argv, argc);
	if(args.size() > 2) {
		this->target = args[1];
		this->source = args[2];
	}	
	else {
		throw std::runtime_error{"Source and traget needed"};
	}
}

const std::filesystem::path & ltn::a::Args::get_target() const {
	return this->target;
}

const std::filesystem::path & ltn::a::Args::get_source() const {
	return this->source;
}
