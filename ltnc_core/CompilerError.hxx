#pragma once
#include <stdexcept>
#include <ostream>
#include <string>
#include <vector>
#include "SourceLocation.hxx"

namespace ltn::c {
	class CompilerError : public std::runtime_error {
	public:
		CompilerError(const std::string & msg, const SourceLocation & info);
		explicit CompilerError(const std::string & msg);
	private:
	};

	inline std::ostream & operator<<(
		std::ostream & out,
		const CompilerError & error) {
		out << error.what() << std::endl;
		return out;
	}
}