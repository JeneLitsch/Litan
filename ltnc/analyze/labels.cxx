#include <sstream>
#include "labels.hxx"

namespace ltn::c {
	namespace {
		std::uint64_t unique_number() {
			static std::uint64_t counter = 0;
			return counter++;
		}
	}

	std::string unique_lambda_label() {
		std::ostringstream oss;
		oss << "_LAMBDA" << unique_number();
		return oss.str();
	}
}