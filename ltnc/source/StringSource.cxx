#include "StringSource.hxx"
#include <sstream>

namespace ltn::c {
	StringSource::StringSource(
		const std::string & code,
		const std::string & name)
		: code {code}
		, name {name} {

	}



	std::unique_ptr<std::istream> StringSource::make_istream() const {
		return std::make_unique<std::istringstream>(this->code);
	}



	std::string StringSource::get_name() const {
		return this->name;
	}
	
	
	
	std::string StringSource::get_full_name() const {
		return this->name;
	}
}