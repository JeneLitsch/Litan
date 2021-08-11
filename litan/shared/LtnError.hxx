#pragma once
#include <stdexcept>
#include <string>
namespace ltn {
	class Error : public std::runtime_error {
	public:
		Error(const std::string & str) : std::runtime_error(str) {}
		virtual std::string str() const { return this->what(); }
	};
	std::ostream & operator<<(
		std::ostream & stream,
		const Error & error);
}