#pragma once
#include <stdexcept>
#include <ostream>
#include <string>

namespace ltn::c {
	class CompilerError : public std::runtime_error {
	public:
		CompilerError(
			const std::string & msg,
			std::size_t line);
	private:
		std::size_t line;
	};

	inline std::ostream & operator<<(
		std::ostream & out,
		const CompilerError & error) {
		out << error.what() << std::endl;
		return out;
	}
}