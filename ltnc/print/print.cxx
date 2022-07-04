#include "print.hxx"
#include <sstream>

namespace ltn::c {
	namespace {
		using namespace inst::args;
		std::string print_args(const None &) {
			return "";
		}

		std::string print_args(const Uint64 & args) {
			std::ostringstream ss;
			ss << args.value;
			return ss.str();
		}

		std::string print_args(const Uint16 & args) {
			std::ostringstream ss;
			ss << args.value;
			return ss.str();
		}

		std::string print_args(const Jump & args) {
			std::ostringstream ss;
			ss << args.name;
			return ss.str();
		}

		std::string print_args(const Target & args) {
			std::ostringstream ss;
			ss << args.name;
			return ss.str();
		}

		std::string print_args(const Jump_Uint64 & args) {
			std::ostringstream ss;
			ss << args.name << " " << args.value;
			return ss.str();
		}

		std::string print_args(const Int64 & args) {
			std::ostringstream ss;
			ss << args.value;
			return ss.str();
		}

		std::string print_args(const Float & args) {
			std::ostringstream ss;
			ss << args.value;
			return ss.str();
		}

		std::string print_args(const Byte & args) {
			std::ostringstream ss;
			ss << static_cast<std::uint16_t>(args.value);
			return ss.str();
		}

		std::string print_args(const Uint64_BytexX & args) {
			std::ostringstream ss;
			ss << args.bytes.size() << " ";
			for(const char byte : args.bytes) {
				ss << static_cast<std::uint16_t>(byte) << " ";
			}
			return ss.str();
		}



		std::string print_instruction(const inst::ExecInst & inst) {
			std::ostringstream ss;
			ss << inst.get_name() << " ";
			return ss.str();
		}

		std::string print_instruction(const inst::Label & inst) {
			std::ostringstream ss;
			ss << ":";
			return ss.str();
		}
	}




	

	std::string print(const std::span<const inst::Instruction> & instructions) {
		std::ostringstream ss;
		for(const auto & inst : instructions) {
			if(const auto * executable = inst.as<inst::ExecInst>()) {
				ss << print_instruction(*executable);
			}
			else if(const auto * label = inst.as<inst::Label>()) {
				ss << print_instruction(*label);
			}

			const auto args = inst.args();
			ss << std::visit([] (const auto & args) {
				return print_args(args);
			}, args);

			ss << "\n";
		}
		return ss.str();
	}
}