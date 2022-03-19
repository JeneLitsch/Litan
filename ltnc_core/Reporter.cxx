#include "Reporter.hxx"
#include "CompilerError.hxx"
#include <sstream>
#include <iostream>

namespace ltn::c {
	void Reporter::may_throw() const {
		if(this->errors.empty()) return;
		std::stringstream ss;
		bool first = true;
		for(const auto & msg : this->errors) {
			if(first) {
				first = false;
			} 
			else {
				ss << "\n";
			}
			ss << msg;
		}
		auto str = ss.str();
		throw CompilerError{str};
	}
}