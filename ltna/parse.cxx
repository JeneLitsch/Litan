#include "parse.hxx"
#include <unordered_map>
#include <sstream>
#include <iostream>

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
		inst::Instruction of_type(std::istream & in) {
			InstT instruction;
			parse_args(instruction.args, in);
			return instruction;
		};

		const std::unordered_map<
			std::string_view,
			inst::Instruction(*)(std::istream &)> table = {
			{ "error",        of_type<inst::Error> },
			{ "exit",         of_type<inst::Exit> },
			{ "state",        of_type<inst::State> },
			{ "try",          of_type<inst::Try> },
			{ "throw",        of_type<inst::Throw> },
			{ "build_in",     of_type<inst::BuildIn> },

			{ "add",          of_type<inst::Add> },
			{ "sub",          of_type<inst::Sub> },
			{ "mlt",          of_type<inst::Mlt> },
			{ "div",          of_type<inst::Div> },
			{ "mod",          of_type<inst::Mod> },

			{ "eql",          of_type<inst::Eql> },
			{ "ueql",         of_type<inst::Ueql> },
			{ "sml",          of_type<inst::Sml> },
			{ "bgr",          of_type<inst::Bgr> },
			{ "smleql",       of_type<inst::Smleql> },
			{ "bgreql",       of_type<inst::Bgreql> },

			{ "shift_l",      of_type<inst::ShiftL> },
			{ "shift_r",      of_type<inst::ShiftR> },

			{ "neg",          of_type<inst::Neg> },
			{ "not",          of_type<inst::Not> },
			{ "inc",          of_type<inst::Inc> },
			{ "dec",          of_type<inst::Dec> },
			
			{ "comp",         of_type<inst::Comp> },
			{ "approx",       of_type<inst::Approx> },
			{ "between",      of_type<inst::Between> },

			{ "newu",         of_type<inst::Newu> },
			{ "newi",         of_type<inst::Newi> },
			{ "newf",         of_type<inst::Newf> },
			{ "newc",         of_type<inst::Newc> },
			{ "true",         of_type<inst::True> },
			{ "false",        of_type<inst::False> },
			{ "null",         of_type<inst::Null> },

			{ "newarr",       of_type<inst::Newarr> },
			{ "newstr",       of_type<inst::Newstr> },
			{ "newout",       of_type<inst::Newout> },
			{ "newin",        of_type<inst::Newin> },
			{ "newfx",        of_type<inst::Newfx> },
			{ "newclock",     of_type<inst::Newclock> },
			{ "newstruct",    of_type<inst::Newstruct> },
			{ "newrange",     of_type<inst::Newrange> },
			{ "newstack",     of_type<inst::Newstack> },
			{ "newqueue",     of_type<inst::Newqueue> },
			{ "newmap",       of_type<inst::Newmap> },
			{ "newrng",       of_type<inst::Newrng> },

			{ "jump",         of_type<inst::Jump> },
			{ "call",         of_type<inst::Call> },
			{ "parameters",   of_type<inst::Params> },
			{ "return",       of_type<inst::Return> },
			{ "ifelse",       of_type<inst::Ifelse> },

			{"invoke",        of_type<inst::Invoke> },
			{"external",      of_type<inst::External> },
			{"capture",       of_type<inst::Capture> },

			{"read",          of_type<inst::Read> },
			{"write",         of_type<inst::Write> },
			{"scrap",         of_type<inst::Scrap> },
			{"duplicate",     of_type<inst::Duplicate> },
			{"makevar",       of_type<inst::Makevar> },
			{"read_x",        of_type<inst::Readx> },
			{"write_x",       of_type<inst::Writex> },
			{"swap",          of_type<inst::Swap> },

			{"read_0",        of_type<inst::Read0> },
			{"read_1",        of_type<inst::Read1> },
			{"read_2",        of_type<inst::Read2> },
			{"read_3",        of_type<inst::Read3> },
			{"write_0",       of_type<inst::Write0> },
			{"write_1",       of_type<inst::Write1> },
			{"write_2",       of_type<inst::Write2> },
			{"write_3",       of_type<inst::Write3> },

			{"out",           of_type<inst::Out> },
			{"stylize",       of_type<inst::Stylize> },
			{"close_stream",  of_type<inst::CloseStream> },
			{"in_str",        of_type<inst::InStr> },
			{"in_line",       of_type<inst::InLine> },
			{"in_bool",       of_type<inst::InBool> },
			{"in_char",       of_type<inst::InChar> },
			{"in_int",        of_type<inst::InInt> },
			{"in_float",      of_type<inst::InFloat> },
			{"in_all",        of_type<inst::InAll> },
			{"is_eof",        of_type<inst::IsEof> },
			{"is_good",       of_type<inst::IsGood> },

			// Math
			{"min",           of_type<inst::Min> },
			{"max",           of_type<inst::Max> },
			{"round",         of_type<inst::Round> },
			{"floor",         of_type<inst::Floor> },
			{"ceil",          of_type<inst::Ceil> },
			{"abs",           of_type<inst::Abs> },
			{"hypot",         of_type<inst::Hypot> },
			{"sqrt",          of_type<inst::Sqrt> },
			{"log",           of_type<inst::Log> },
			{"ln",            of_type<inst::Ln> },
			{"pow",           of_type<inst::Pow> },

			{"sin",           of_type<inst::Sin> },
			{"cos",           of_type<inst::Cos> },
			{"tan",           of_type<inst::Tan> },

			// bitwise
			{"bitand",        of_type<inst::Bitand> },
			{"bitor",         of_type<inst::Bitor> },
			{"bitxor",        of_type<inst::Bitxor> },
			{"bitnot",        of_type<inst::Bitnot> },

			// Array Utils
			{"size",          of_type<inst::Size> },
			{"at",            of_type<inst::At> },
			{"at_write",      of_type<inst::AtWrite> },
			{"front",         of_type<inst::Front> },
			{"back",          of_type<inst::Back> },
			{"insert",        of_type<inst::Insert> },
			{"remove",        of_type<inst::Remove> },
			{"begin",         of_type<inst::Begin> },
			{"end",           of_type<inst::End> },
			{"push",          of_type<inst::Push> },
			{"pop",           of_type<inst::Pop> },
			{"peek",          of_type<inst::Peek> },
			{"contains",      of_type<inst::Contains> },

			// Chrono utils
			{"cast_char",     of_type<inst::CastChar> },
			{"cast_bool",     of_type<inst::CastBool> },
			{"cast_int",      of_type<inst::CastInt> },
			{"cast_float",    of_type<inst::CastFloat> },
			{"cast_string",   of_type<inst::CastString> },
			{"cast_array",    of_type<inst::CastArray> },

			// Type utils
			{"typeid",        of_type<inst::TypeId>},
			{"clone",         of_type<inst::Clone> },

			{"member_read",   of_type<inst::MemberRead> },
			{"member_write",  of_type<inst::MemberWrite> },
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