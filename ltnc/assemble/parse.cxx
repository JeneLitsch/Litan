#include "parse.hxx"
#include <unordered_map>
#include <sstream>
#include <iostream>
#include "stdxx/array.hxx"

namespace ltn::c {
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
			std::size_t count;
			in >> count;
			for(std::size_t i = 0; i < count; ++i) {
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



		template<typename InstT>
		constexpr std::pair<std::string_view, inst::Instruction(*)(std::istream &)> create_entry() {
			return { InstT::name, parse_args<InstT> };
		}



		const auto table = std::unordered_map {
			create_entry<ltn::inst::Label>(),
		
			create_entry<ltn::inst::Exit>(),
			create_entry<ltn::inst::Error>(),
			create_entry<ltn::inst::State>(),
			create_entry<ltn::inst::Try>(),
			create_entry<ltn::inst::Throw>(),
			create_entry<ltn::inst::BuildIn>(),
			
			create_entry<ltn::inst::Add>(),
			create_entry<ltn::inst::Sub>(),
			create_entry<ltn::inst::Mlt>(),
			create_entry<ltn::inst::Div>(),
			create_entry<ltn::inst::Mod>(),
			
			create_entry<ltn::inst::Eql>(),
			create_entry<ltn::inst::Ueql>(),
			create_entry<ltn::inst::Sml>(),
			create_entry<ltn::inst::Bgr>(),
			create_entry<ltn::inst::Smleql>(),
			create_entry<ltn::inst::Bgreql>(),
			
			create_entry<ltn::inst::ShiftL>(),
			create_entry<ltn::inst::ShiftR>(),
			
			create_entry<ltn::inst::Neg>(),
			create_entry<ltn::inst::Not>(),
			create_entry<ltn::inst::Inc>(),
			create_entry<ltn::inst::Dec>(),
			
			create_entry<ltn::inst::Comp>(),
			create_entry<ltn::inst::Between>(), 
			
			create_entry<ltn::inst::Newu>(),
			create_entry<ltn::inst::Newi>(),
			create_entry<ltn::inst::Newf>(),
			create_entry<ltn::inst::Newc>(),
			create_entry<ltn::inst::True>(),
			create_entry<ltn::inst::False>(),
			create_entry<ltn::inst::Null>(),
			
			create_entry<ltn::inst::Newarr>(),
			create_entry<ltn::inst::Newstr>(),
			create_entry<ltn::inst::Newout>(),
			create_entry<ltn::inst::Newin>(),
			create_entry<ltn::inst::Newfx>(),
			create_entry<ltn::inst::Newclock>(),
			create_entry<ltn::inst::Newstruct>(),
			create_entry<ltn::inst::Newrange>(),
			create_entry<ltn::inst::Newstack>(),
			create_entry<ltn::inst::Newqueue>(),
			create_entry<ltn::inst::Newmap>(),
			create_entry<ltn::inst::Newrng>(),
			
			create_entry<ltn::inst::Jump>(),
			create_entry<ltn::inst::Call>(),
			create_entry<ltn::inst::Params>(),
			create_entry<ltn::inst::Return>(),
			create_entry<ltn::inst::Ifelse>(),
			
			create_entry<ltn::inst::Invoke>(),
			create_entry<ltn::inst::External>(),
			create_entry<ltn::inst::Capture>(),
			
			create_entry<ltn::inst::Read>(),
			create_entry<ltn::inst::Write>(),
			create_entry<ltn::inst::Scrap>(),
			create_entry<ltn::inst::Duplicate>(),
			create_entry<ltn::inst::Makevar>(),
			create_entry<ltn::inst::Readx>(),
			create_entry<ltn::inst::Writex>(),
			create_entry<ltn::inst::Swap>(),
			
			create_entry<ltn::inst::Read0>(),
			create_entry<ltn::inst::Read1>(),
			create_entry<ltn::inst::Read2>(),
			create_entry<ltn::inst::Read3>(),
			
			create_entry<ltn::inst::Write0>(),
			create_entry<ltn::inst::Write1>(),
			create_entry<ltn::inst::Write2>(),
			create_entry<ltn::inst::Write3>(),
			
			create_entry<ltn::inst::Out>(),
			create_entry<ltn::inst::Stylize>(),
			create_entry<ltn::inst::CloseStream>(),
			create_entry<ltn::inst::InStr>(),
			create_entry<ltn::inst::InLine>(),
			create_entry<ltn::inst::InBool>(),
			create_entry<ltn::inst::InChar>(),
			create_entry<ltn::inst::InInt>(),
			create_entry<ltn::inst::InFloat>(),
			create_entry<ltn::inst::InAll>(),
			create_entry<ltn::inst::IsEof>(),
			create_entry<ltn::inst::IsGood>(),
			
			create_entry<ltn::inst::Min>(),
			create_entry<ltn::inst::Max>(),
			create_entry<ltn::inst::Round>(),
			create_entry<ltn::inst::Floor>(),
			create_entry<ltn::inst::Ceil>(),
			create_entry<ltn::inst::Abs>(),
			create_entry<ltn::inst::Hypot>(),
			create_entry<ltn::inst::Sqrt>(),
			create_entry<ltn::inst::Log>(),
			create_entry<ltn::inst::Ln>(),
			create_entry<ltn::inst::Pow>(),

			create_entry<ltn::inst::Sin>(),
			create_entry<ltn::inst::Cos>(),
			create_entry<ltn::inst::Tan>(),
			
			create_entry<ltn::inst::Bitand>(),
			create_entry<ltn::inst::Bitor>(),
			create_entry<ltn::inst::Bitxor>(),
			create_entry<ltn::inst::Bitnot>(),
			
			create_entry<ltn::inst::Size>(),
			create_entry<ltn::inst::At>(),
			create_entry<ltn::inst::AtWrite>(),
			create_entry<ltn::inst::Front>(),
			create_entry<ltn::inst::Back>(),
			create_entry<ltn::inst::Insert>(),
			create_entry<ltn::inst::Remove>(),
			create_entry<ltn::inst::Begin>(),
			create_entry<ltn::inst::End>(),
			create_entry<ltn::inst::Push>(),
			create_entry<ltn::inst::Pop>(),
			create_entry<ltn::inst::Peek>(),
			create_entry<ltn::inst::Contains>(),
			
			create_entry<ltn::inst::CastChar>(),
			create_entry<ltn::inst::CastBool>(),
			create_entry<ltn::inst::CastInt>(),
			create_entry<ltn::inst::CastFloat>(),
			create_entry<ltn::inst::CastString>(),
			create_entry<ltn::inst::CastArray>(),
			
			create_entry<ltn::inst::TypeId>(),
			create_entry<ltn::inst::Clone>(),
			
			create_entry<ltn::inst::MemberRead>(),
			create_entry<ltn::inst::MemberWrite>()
		};
	}

	

	std::vector<inst::Instruction> parse(std::istream & in) {
		std::vector<inst::Instruction> instructions;
		std::string line;
		while (std::getline(in, line)) {
			std::istringstream iss{line};
			std::string name;
			iss >> name;
			if(!name.empty() && name[0] == ':') {
				instructions.push_back(inst::Label{name.substr(1)});
			}
			else if(!name.empty()) {
				instructions.push_back(table.at(name)(iss));
			}
		}
		return instructions;
	}
}