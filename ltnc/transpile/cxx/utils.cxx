#include "utils.hxx"

namespace ltn::c::trans {
	std::string to_lowercase(std::string_view in) {
		std::string out;
		std::transform(in.begin(), in.end(), std::back_inserter(out),
			[](char c){ return std::tolower(c);
		});
		return out;
	} 


	std::string to_uppercase(std::string_view in) {
		std::string out;
		std::transform(in.begin(), in.end(), std::back_inserter(out),
			[](char c){ return std::toupper(c);
		});
		return out;
	} 


	
	std::string to_capitalized(std::string_view in) {
		std::string out = std::string{in};
		if(!std::empty(out)) out.front() = std::toupper(out.front());
		return out;
	} 
}