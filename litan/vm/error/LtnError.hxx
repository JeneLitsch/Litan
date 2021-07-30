#pragma once
#include <stdexcept>
#include <string>
namespace ltn {
	class Error : public std::runtime_error {
	public:
		Error();
		Error(const std::string & msg);
	};
}