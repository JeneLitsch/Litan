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
		std::string expandLiteral(std::istream & line, const std::string_view & inst) {
			std::stringstream ss;
			Value value;
			line >> value;
			const auto bytes = toBytes(value);
			ss << inst << "\n";
			for(const std::uint8_t byte : bytes) {
				ss << "byte " << std::hex << unsigned(byte) << "\n"; 
			}
			return ss.str();
		}

		void expandLine(const std::string & line, std::ostream & out) {
			std::stringstream ls(line);
			std::string inst;
			ls >> inst;

			if(inst == "newref") {
				out << expandLiteral<std::uint64_t>(ls, "newref");
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
			if(inst == "jump") {
				out << expandLiteral<std::uint64_t>(ls, "jump");
				return;
			}
			if(inst == "call") {
				out << expandLiteral<std::uint64_t>(ls, "call");
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