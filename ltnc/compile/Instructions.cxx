#include "Instructions.hxx"
#include <sstream>

namespace ltn::c::compile::inst {
	std::string comment(std::string msg) {
		return "// " + msg + "\n";
	}

	std::string jumpmark(const std::string_view name) {
		std::stringstream ss;
		ss << ":" << name << "\n";
		return ss.str(); 
	}

	std::string byte(std::uint8_t byte) {
		std::stringstream ss;
		ss 	<< "byte "
			<< std::hex << static_cast<unsigned>(byte) << "\n";
		return ss.str(); 
	}

	std::string jump(const std::string_view & to) {
		std::stringstream ss;
		ss 	<< "jump " << to << "\n";
		return ss.str();
	}

	std::string call(const std::string_view & to) {
		std::stringstream ss;
		ss 	<< "call " << to << "\n";
		return ss.str();
	}

	const std::string newu(std::uint64_t value) {
		std::stringstream ss;
		ss << "newu " << value << "\n";
		return ss.str();
	}

	const std::string newi(std::int64_t value) {
		std::stringstream ss;
		ss << "newi " << value << "\n";
		return ss.str();
	}

	const std::string newf(double value) {
		std::stringstream ss;
		ss << "newf " << value << "\n";
		return ss.str();
	}

	const std::string newref(std::uint64_t value) {
		std::stringstream ss;
		ss << "newref " << value << "\n";
		return ss.str();
	}

}