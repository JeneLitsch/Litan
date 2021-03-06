#pragma once
#include <stdexcept>
#include <ostream>
#include <string>
#include <vector>
#include "SourceLocation.hxx"

namespace ltn::c {
	// Buffers errors
	class Reporter {
	public:
		void push(const auto & error) {
			this->errors.push_back(error.what());
		}

		Reporter & operator<<(const auto & error) {
			this->push(error);
			return *this;
		} 

		void may_throw() const;
	private:
		std::vector<std::string> errors;
	};
}