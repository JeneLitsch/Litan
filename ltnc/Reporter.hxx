#pragma once
#include <stdexcept>
#include <ostream>
#include <string>
#include <vector>
#include "ltnc/SourceLocation.hxx"

namespace ltn::c {
	// Buffers errors
	class Reporter {
	public:
		void push(const auto & error) {
			this->errors.push_back(error.what());
		}

		void may_throw() const;
	private:
		std::vector<std::string> errors;
	};
}