#include "print.hxx"
#include <sstream>

namespace ltn::c {
	namespace {
		std::string print_inst(const inst::InstLabel & inst) {
			return ":" + inst.label;
		}

		std::string print_inst(const inst::InstNone & inst) {
			return std::string{inst.name};
		}

		std::string print_inst(const inst::InstUint64 & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.value;
			return ss.str();
		}

		std::string print_inst(const inst::InstUint16 & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.value;
			return ss.str();
		}

		std::string print_inst(const inst::InstJump & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.label;
			return ss.str();
		}

		std::string print_inst(const inst::InstTarget & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.name;
			return ss.str();
		}

		std::string print_inst(const inst::InstJumpUint64 & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.label << " " << args.value;
			return ss.str();
		}

		std::string print_inst(const inst::InstInt64 & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.value;
			return ss.str();
		}

		std::string print_inst(const inst::InstFloat & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.value;
			return ss.str();
		}

		std::string print_inst(const inst::InstByte & args) {
			std::ostringstream ss;
			ss << args.name << " " << static_cast<std::uint16_t>(args.value);
			return ss.str();
		}

		std::string print_inst(const inst::InstUint64Bytex & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.bytes.size() << " ";
			for(const char byte : args.bytes) {
				ss << static_cast<std::uint16_t>(byte) << " ";
			}
			return ss.str();
		}

		std::string print_inst(const inst::InstBytex0 & args) {
			std::ostringstream ss;
			ss << args.name << " ";
			for(const char byte : args.bytes) {
				ss << static_cast<std::uint16_t>(byte) << " ";
			}
			ss << "\\0";
			return ss.str();
		}
	}




	

	std::string print(const std::span<const inst::Inst> & instructions) {
		std::ostringstream ss;
		for(const auto & inst : instructions) {
			ss << std::visit([] (const auto & args) {
				return print_inst(args);
			}, inst);

			ss << "\n";
		}
		return ss.str();
	}
}