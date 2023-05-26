#pragma once
#include <string>
#include <sstream>
#include "ltnvm/Value.hxx"

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


	
	struct Unhandled {
		Exception exception;
	};



	namespace except {
		inline Exception invalid_argument(
			const std::string & msg = "Invalid argument") {
			return {Exception::Type::INVALID_ARGUMENT, msg};
		}
		
		inline Exception invalid_operands() {
			return invalid_argument("Invalid operands");
		}

		inline Exception not_output() {
			return invalid_argument("Not an output stream");
		}

		inline Exception not_input() {
			return invalid_argument("Not an input stream");
		}

		inline Exception invalid_parameters(std::size_t expected, std::size_t got) {
			std::ostringstream ss;
			ss << "Invalid parameters: Expected " << expected << " got " << got;
			return invalid_argument(ss.str());
		}

		inline Exception invalid_cast(const std::string & toType) {
			return invalid_argument("Invalid cast to " + toType);
		}

		inline Exception cannot_open_file(const std::string & path) {
			return {Exception::Type::FILE_ERROR,
				"Cannot open file: \"" + path + "\""};
		}

		inline Exception division_by_zero(
			const std::string & msg = "Division by 0"){
			return {Exception::Type::DIVISION_BY_0, msg};
		}

		inline Exception out_of_range(
			const std::string & msg = "Out of range") {
			return {Exception::Type::OUT_OF_RANGE, msg};
		}

		inline Exception negative_index() {
			return out_of_range("Out of range: negative index");
		}

		inline Exception empty_collection() {
			return out_of_range("Out of range: empty collection");
		}

		inline Exception invalid_member_access() {
			return {Exception::Type::INVALID_MEMBER_ACCESS,
				"Invalid member access"};
		}

		inline Exception missing_operator(const std::string & op) {
			return {Exception::Type::INVALID_MEMBER_ACCESS,
				"Object has no overload for operator" + op};
		}
	}
}