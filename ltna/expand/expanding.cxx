#include "expanding.hxx"
#include <sstream>
#include <array>
#include <ranges>
#include "ltn/Bitcast.hxx"
#include "ltna/InstructionTable.hxx"
#include "ltn/reading.hxx"
namespace ltn::a::expand {
	namespace {

		template<typename T>
		concept not_usigned_integral = !std::is_unsigned<T>::value;
		
		auto toBytes(std::unsigned_integral auto value) {
			constexpr static auto SIZE = sizeof(value) / sizeof(std::uint8_t);
			std::array<std::uint8_t, SIZE> bytes;
			for(std::uint8_t & byte : bytes) {
				byte = value & 0xff;
				value >>= 8;
			}
			std::reverse(bytes.begin(), bytes.end());
			return bytes;
		}
		
		auto toBytes(not_usigned_integral auto value) {
			return toBytes(bitcast<std::uint64_t>(value));
		}

		template<typename Value>
		std::string expandArg(std::istream & line) {
			std::stringstream ss;
			const auto value = read<Value>(line);
			const auto bytes = toBytes(value);
			for(const std::uint8_t byte : bytes) {
				ss << "byte " << std::hex << +byte << "\n"; 
			}
			return ss.str();
		}

		std::string expandBytes(std::size_t byteCount, std::istream & ls) {
			std::stringstream ss;
			for(std::size_t i = 0; i < byteCount; i++) {
				const auto byte = read<unsigned>(ls >> std::hex);
				ss	<< "byte " << std::hex << byte << "\n";
			}
			return ss.str();
		}

		bool isSpace(char chr) {
			return std::isspace(chr);
		}

	}

	void expand(std::istream & in, std::ostream & out) {
		std::string line;
		while(std::getline(in >> std::ws, line)) {
			std::stringstream ls(line);
			
			if(std::all_of(line.begin(), line.end(), isSpace)) {
				return;
			}
			
			const auto inst = read<std::string>(ls);
			if(!instructionTable.contains(inst)) {
				return;
			}
			const auto argFormat = instructionTable.at(inst).argFormat;
			
			out << inst << "\n";
			
			switch (argFormat) {
				case ArgFormat::NONE:
					break;

				case ArgFormat::UINT:
				case ArgFormat::JUMP:
					out << expandArg<std::uint64_t>(ls);
					break;

				case ArgFormat::UINTx2:
				case ArgFormat::JUMP_UINT:
					out << expandArg<std::uint64_t>(ls);
					out << expandArg<std::uint64_t>(ls);
					break;

				case ArgFormat::INT:
					out << expandArg<std::int64_t>(ls);
					break;

				case ArgFormat::FLOAT:
					out << expandArg<double>(ls);
					break;

				case ArgFormat::BYTE:
				case ArgFormat::CHAR:
					out << expandBytes(1, ls);
					break;

				case ArgFormat::BYTEx2:
					out << expandBytes(2, ls);
					break;

				case ArgFormat::CHARx4:
					out << expandBytes(4, ls);
					break;

				case ArgFormat::CHARx8:
					out << expandBytes(8, ls);
					break;
			}
		}
	}
}