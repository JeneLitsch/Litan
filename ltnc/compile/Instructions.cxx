#include "Instructions.hxx"
#include <sstream>

namespace ltn::c::compile::inst {
	const std::string comment(std::string msg) {
		return "// " + msg + "\n";
	}

	const std::string jumpmark(const std::string_view name) {
		std::stringstream ss;
		ss << ":" << name << "\n";
		return ss.str(); 
	}

	const std::string byte(std::uint8_t byte) {
		std::stringstream ss;
		ss 	<< "byte "
			<< std::hex << static_cast<unsigned>(byte) << "\n";
		return ss.str(); 
	}

	const std::string jump(const std::string_view & to) {
		std::stringstream ss;
		ss 	<< "jump " << to << "\n";
		return ss.str();
	}

	const std::string call(const std::string_view & to) {
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

	const std::string addr(std::uint64_t value) {
		std::stringstream ss;
		ss << "addr " << value << "\n";
		return ss.str();
	}

	const std::string ifelse(const std::string_view & to) {
		std::stringstream ss;
		ss << "ifelse " << to << "\n";
		return ss.str();
	}

	const std::string ch4r(char chr) {
		std::stringstream ss;
		ss << "char " << std::hex << static_cast<int>(chr) << "\n";
		return ss.str();
	}


	const std::string newfx(
		const std::string_view & fxName,
		std::size_t params) {
		std::stringstream ss;
		ss 	<< "newfx " << fxName << " "
			<< std::hex << static_cast<int>(params) << "\n";
		return ss.str();
	}

	const std::string read_x(std::uint64_t addr) {
		std::stringstream ss;
			switch (addr) {
			// Shortcut instructions
			case 0: ss << inst::read_0; break;
			case 1: ss << inst::read_1; break;
			case 2: ss << inst::read_2; break;
			case 3: ss << inst::read_3; break;
			// Standard instructions
			default: ss << "read_x " << addr << "\n"; break;
		}
		return ss.str();
	}

	const std::string write_x(std::uint64_t addr) {
		std::stringstream ss;
		switch (addr) {
		// Shortcut instructions
		case 0: ss << inst::write_0; break;
		case 1: ss << inst::write_1; break;
		case 2: ss << inst::write_2; break;
		case 3: ss << inst::write_3; break;
		// Standard instructions
		default: ss << "write_x " << addr << "\n"; break;
		}
		return ss.str();
		
	}
}