#include "parse.hxx"
#include <unordered_map>
#include <sstream>
#include <iostream>
#include "stdxx/array.hxx"
#include "stdxx/constexpr_table.hxx"

namespace ltn::a {
	namespace {
		using namespace inst::args;
		void parse_args(None &, std::istream & in) {}

		void parse_args(Uint64 & args, std::istream & in) {
			in >> args.value;
		}

		void parse_args(Uint16 & args, std::istream & in) {
			in >> args.value;
		}

		void parse_args(Jump & args, std::istream & in) {
			in >> args.name;
		}

		void parse_args(Target & args, std::istream & in) {
			in >> args.name;
		}

		void parse_args(Jump_Uint64 & args, std::istream & in) {
			in >> args.name;
			in >> args.value;
		}

		void parse_args(Int64 & args, std::istream & in) {
			in >> args.value;
		}

		void parse_args(Float & args, std::istream & in) {
			in >> args.value;
		}

		void parse_args(Byte & args, std::istream & in) {
			std::uint16_t value;
			in >> value;
			args.value = static_cast<std::uint8_t>(value);
		}

		void parse_args(Uint64_BytexX & args, std::istream & in) {
			in >> args.value;
			for(std::size_t i = 0; i < args.value; ++i) {
				std::uint16_t value;
				in >> value;
				args.bytes.push_back(static_cast<std::uint8_t>(value));
			}
		}

		template<typename InstT>
		inst::Instruction parse_args(std::istream & in) {
			InstT instruction;
			parse_args(instruction.args, in);
			return instruction;
		};



		struct EntryMaker {
			using return_type = std::pair<
				std::string_view,
				inst::Instruction(*)(std::istream &)>;
			template<typename InstT>
			static constexpr return_type create() {
				return { 
					InstT::name,
					parse_args<InstT> };
			};
		};



		const auto table = stx::constexpr_unordered_map<EntryMaker, inst::Instruction>();
	}
	


	std::vector<inst::Instruction> parse(std::istream & in) {
		std::vector<inst::Instruction> instructions;
		std::string line;
		while (std::getline(in, line)) {
			std::istringstream iss{line};
			std::string name;
			iss >> name;
			if(!name.empty() && name[0] == ':') {
				instructions.push_back(inst::Label{
					inst::args::Target{name.substr(1)}}
				);
			}
			else if(!name.empty()) {
				instructions.push_back(table.at(name)(iss));
			}
		}
		return instructions;
	}
}