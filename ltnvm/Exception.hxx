#pragma once
#include <string>
#include <sstream>

namespace ltn::vm {	
	struct Exception {
		enum class Type {
			GENERIC_ERROR,
			INVALID_ARGUMENT,
			FILE_ERROR,
			DIVISION_BY_0,
			OUT_OF_RANGE,
			INVALID_MEMBER_ACCESS,
		};
		Type type = Type::GENERIC_ERROR;
		std::string msg;
	};

	namespace except {
		inline Exception invalidArgument(
			const std::string & msg = "Invalid argument") {
			return {Exception::Type::INVALID_ARGUMENT, msg};
		}
		
		inline Exception invalidOperands() {
			return invalidArgument("Invalid operands");
		}

		inline Exception notOutput() {
			return invalidArgument("Not an output stream");
		}

		inline Exception notInput() {
			return invalidArgument("Not an input stream");
		}

		inline Exception invalidParameters(std::size_t expected, std::size_t got) {
			std::ostringstream ss;
			ss << "Invalid paramters: Expected " << expected << " got " << got;
			return invalidArgument(ss.str());
		}

		inline Exception invalidCast(const std::string & toType) {
			return invalidArgument("Invalid cast to " + toType);
		}

		inline Exception cannotOpenFile(const std::string & path) {
			return {Exception::Type::FILE_ERROR,
				"Cannot open file: \"" + path + "\""};
		}

		inline Exception divisionBy0(
			const std::string & msg = "Division by 0"){
			return {Exception::Type::DIVISION_BY_0, msg};
		}

		inline Exception outOfRange(
			const std::string & msg = "Out of range") {
			return {Exception::Type::OUT_OF_RANGE, msg};
		}

		inline Exception negativeIndex() {
			return outOfRange("Out of range: negative index");
		}

		inline Exception emptyCollection() {
			return outOfRange("Out of range: empty collection");
		}

		inline Exception invalidMemberAccess() {
			return {Exception::Type::INVALID_MEMBER_ACCESS,
				"Invalid member access"};
		}
	}
}