#include "expanding.hxx"
#include <sstream>
#include <array>
#include "ltn/Bitcast.hxx"
#include "ltna/InstructionTable.hxx"
namespace ltn::a::expand {
	namespace {
		
		auto toBytes(std::integral auto value) {
			constexpr static auto SIZE 
				= sizeof(decltype(value))
				/ sizeof(std::uint8_t);
			std::array<std::uint8_t, SIZE> bytes;
			for(std::uint8_t & byte : bytes) {
				byte = value & 0xff;
				value >>= 8;
			}
			std::reverse(bytes.begin(), bytes.end());
			return bytes;
		}
		
		auto toBytes(std::int64_t value) {
			return toBytes(bitcast<std::uint64_t>(value));
		}

		auto toBytes(double value) {
			return toBytes(bitcast<std::uint64_t>(value));
		}

		template<typename Value>
		std::string expandArg(std::istream & line) {
			std::stringstream ss;
			Value value;
			line >> value;
			const auto bytes = toBytes(value);
			for(const std::uint8_t byte : bytes) {
				ss << "byte " << std::hex << +byte << "\n"; 
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

		std::string expandBytes(const std::string_view inst, std::size_t x, std::istream & ls) {
			std::stringstream ss;
			unsigned chr;
			ss << inst << "\n";
			for(std::size_t i = 0; i < x; i++) {
				ls >> std::hex >> chr;
				ss	<< "byte " << std::hex << chr << "\n";
			}
			return ss.str();
		}
	}


	void expand(std::istream & in, std::ostream & out) {
		std::string line;
		while(std::getline(in >> std::ws, line)) {
			std::stringstream ls(line);
			std::string inst;
			ls >> inst;

			if(instructionTable.contains(inst)) {
				const auto [opcode, size, args] = instructionTable.at(inst);
				switch (args) {
					case InstArgs::NONE: {
						if(line != "") {
							out << line << "\n";
						}
					} break;

					case InstArgs::UINT: {
						out << expandLiteral<std::uint64_t>(ls, inst);
					} break;

					case InstArgs::UINTx2: {
						out << expandLiteral<std::uint64_t>(ls, inst);
						out << expandArg<std::uint64_t>(ls);
					} break;

					case InstArgs::INT: {
						out << expandLiteral<std::int64_t>(ls, inst);
					} break;

					case InstArgs::FLOAT: {
						out << expandLiteral<double>(ls, inst);
					} break;

					case InstArgs::BYTE: [[fallthrough]];

					case InstArgs::CHAR: {
						out << expandBytes(inst, 1, ls);
					} break;

					case InstArgs::CHAR_4: {
						out << expandBytes(inst, 4, ls);
					} break;

					case InstArgs::CHAR_8: {
						out << expandBytes(inst, 8, ls);
					} break;
				}
			}
		}
	}
}