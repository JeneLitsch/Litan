#include "expanding.hxx"
#include <sstream>
#include <iostream>
#include <array>
#include <ranges>
#include "ltn/bitcast.hxx"
#include "ltna/InstructionTable.hxx"
#include "ltn/reading.hxx"
#include "ltn/float64_t.hxx"
namespace ltn::a::expand {
	namespace {
		auto to_bytes(std::unsigned_integral auto value) {
			constexpr static auto SIZE = sizeof(value) / sizeof(std::uint8_t);
			std::array<std::uint8_t, SIZE> bytes;
			for(std::uint8_t & byte : bytes) {
				byte = value & 0xff;
				value >>= 8;
			}
			std::reverse(bytes.begin(), bytes.end());
			return bytes;
		}
		


		auto to_bytes(std::signed_integral auto value) {
			using T = std::make_unsigned_t<decltype(value)>;
			return to_bytes(bitcast<T>(value));
		}



		auto to_bytes(std::floating_point auto value) {
			return to_bytes(bitcast<std::uint64_t>(value));
		}



		template<typename Value>
		std::string expandArg(std::istream & line) {
			std::stringstream ss;
			const auto value = read<Value>(line);
			const auto bytes = to_bytes(value);
			for(const std::uint8_t byte : bytes) {
				ss << "byte " << std::hex << +byte << "\n"; 
			}
			return ss.str();
		}

		std::string expand_bytes(std::size_t byteCount, std::istream & ls) {
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
			if(!instruction_table.contains(inst)) {
				return;
			}
			const auto argFormat = instruction_table.at(inst).arg_format;
			
			out << inst << "\n";
			
			switch (argFormat) {
				case ArgFormat::NONE:
					break;

				case ArgFormat::UINT:   [[fallthrough]];
				case ArgFormat::JUMP:
					out << expandArg<std::uint64_t>(ls);
					break;

				case ArgFormat::UINT16: 
					out << expandArg<std::uint16_t>(ls >> std::hex);
					break;

				case ArgFormat::UINTx2: [[fallthrough]];
				case ArgFormat::JUMP_UINT:
					out << expandArg<std::uint64_t>(ls);
					out << expandArg<std::uint64_t>(ls);
					break;

				case ArgFormat::INT:
					out << expandArg<std::int64_t>(ls);
					break;

				case ArgFormat::FLOAT:
					out << expandArg<stx::float64_t>(ls);
					break;

				case ArgFormat::BYTE:
					out << expand_bytes(1, ls);
					break;

				case ArgFormat::UINT_BYTExX:
					const auto size = read<std::uint64_t>(ls);
					const auto bytes = to_bytes(size);
					for(const std::uint8_t byte : bytes) {
						out << "byte " << std::hex << +byte << "\n"; 
					}
					out << expand_bytes(size, ls);
					break;
			}
		}
	}
}