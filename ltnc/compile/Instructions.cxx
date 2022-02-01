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


	const std::string read_captured(std::uint64_t index) {
		std::stringstream ss;
		ss << "read_captured " << index << "\n"; 
		return ss.str();
	}

	const std::string parameters(std::uint64_t count) {
		std::stringstream ss;
		ss << "parameters " << count << "\n"; 
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

	const std::string char_8(std::string_view & str) {
		std::stringstream ss;
		ss << "char_8 ";
		for(std::size_t i = 0; i < 8; i++) {
			ss << std::hex << int(str.front()) << " ";
			str.remove_prefix(1);
		}
		ss << "\n";
		return ss.str();
	}

	const std::string char_4(std::string_view & str) {
		std::stringstream ss;
		ss << "char_4 ";
		for(std::size_t i = 0; i < 4; i++) {
			ss << std::hex << int(str.front()) << " ";
			str.remove_prefix(1);
		}
		ss << "\n";
		return ss.str();
	}

	const std::string member_read(std::uint64_t addr) {
		std::stringstream ss;
		ss << "member_read " << addr << "\n";
		return ss.str();	
	}

	const std::string member_write(std::uint64_t addr) {
		std::stringstream ss;
		ss << "member_write " << addr << "\n";
		return ss.str();	
	}

}