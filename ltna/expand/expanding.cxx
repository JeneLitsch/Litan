#include "expanding.hxx"
#include <sstream>
#include <array>
namespace ltn::a::expand {
	namespace {

		auto toBytes(std::uint64_t value) {
			std::array<std::uint8_t, 8> bytes;
			for(std::uint8_t & byte : bytes) {
				byte = value & 0xff;
				value >>= 8;
			}
			std::reverse(bytes.begin(), bytes.end());
			return bytes;
		}
		
		auto toBytes(std::int64_t value) {
			return toBytes(*reinterpret_cast<std::uint64_t*>(&value));
		}

		auto toBytes(double value) {
			return toBytes(*reinterpret_cast<std::uint64_t*>(&value));
		}

		template<typename Value>
		std::string expandArg(std::istream & line) {
			std::stringstream ss;
			Value value;
			line >> value;
			const auto bytes = toBytes(value);
			for(const std::uint8_t byte : bytes) {
				ss << "byte " << std::hex << unsigned(byte) << "\n"; 
			}
			return ss.str();
		}

		template<typename Value>
		std::string expandLiteral(std::istream & line, const std::string_view & inst) {
			std::stringstream ss;
			ss << inst << "\n";
			ss << expandArg<Value>(line);
			return ss.str();
		}

		void expandLine(const std::string & line, std::ostream & out) {
			std::stringstream ls(line);
			std::string inst;
			ls >> inst;

			if(inst == "read_x") {
				out << expandLiteral<std::uint64_t>(ls, "read_x");
				return;
			}
			if(inst == "write_x") {
				out << expandLiteral<std::uint64_t>(ls, "write_x");
				return;
			}
			if(inst == "addr") {
				out << expandLiteral<std::uint64_t>(ls, "addr");
				return;
			}
			if(inst == "newu") {
				out << expandLiteral<std::uint64_t>(ls, "newu");
				return;
			}
			if(inst == "newi") {
				out << expandLiteral<std::int64_t>(ls, "newi");
				return;
			}
			if(inst == "newf") {
				out << expandLiteral<double>(ls, "newf");
				return;
			}
			if(inst == "newfx") {
				std::stringstream ss;
				ss << expandLiteral<std::uint64_t>(ls, "newfx");
				ss << expandArg<std::uint64_t>(ls);
				out << ss.str();
				return;
			}
			if(inst == "jump") {
				out << expandLiteral<std::uint64_t>(ls, "jump");
				return;
			}
			if(inst == "call") {
				out << expandLiteral<std::uint64_t>(ls, "call");
				return;
			}
			if(inst == "ifelse") {
				out << expandLiteral<std::uint64_t>(ls, "ifelse");
				return;
			}
			if(inst == "char") {
				ls >> std::ws;
				std::string chr;
				ls >> chr;
				out << "char\n";
				out	<< "byte " << std::hex << chr << "\n";
				return;
			}
			if(line != "") {
				out << line << "\n";
			}
		}
	}


	void expand(std::istream & in, std::ostream & out) {
		std::string line;
		while(std::getline(in >> std::ws, line)) {
			expandLine(line, out);
		}
	}
}