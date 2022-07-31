#include "assemble.hxx"
#include "stdxx/casting.hxx"
#include "stdxx/array.hxx"
#include <iostream>
#include "ltn/version.hxx"

namespace ltn::c {
	namespace {
		using namespace ltn::inst::args;
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
			return to_bytes(stx::bitcast<T>(value));
		}
		auto to_bytes(std::floating_point auto value) {
			return to_bytes(stx::bitcast<std::uint64_t>(value));
		}
		


		void assemble_args(
			std::vector<std::uint8_t> &,
			const None &,
			const AddressTable &) {
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const Uint64 & args,
			const AddressTable &) {
			const auto bytes = to_bytes(args.value);
			for(const auto byte : bytes) {
				bytecode.push_back(byte);
			}
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const Uint16 & args,
			const AddressTable &) {
			const auto bytes = to_bytes(args.value);
			for(const auto byte : bytes) {
				bytecode.push_back(byte);
			}
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const Jump & args,
			const AddressTable & jump_table) {
			const auto addr = jump_table.at(args.name);
			const auto bytes = to_bytes(addr);
			for(const auto byte : bytes) {
				bytecode.push_back(byte);
			}
		}
		void assemble_args(
			std::vector<std::uint8_t> &,
			const Target &,
			const AddressTable &) {
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const Jump_Uint64 & args,
			const AddressTable & jump_table) {
			const auto bytes_jump = to_bytes(jump_table.at(args.name));
			for(const auto byte : bytes_jump) {
				bytecode.push_back(byte);
			}
			const auto bytes_value = to_bytes(args.value);
			for(const auto byte : bytes_value) {
				bytecode.push_back(byte);
			}
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const Int64 & args,
			const AddressTable &) {
			const auto bytes = to_bytes(args.value);
			for(const auto byte : bytes) {
				bytecode.push_back(byte);
			}
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const Float & args,
			const AddressTable &) {
			const auto bytes = to_bytes(args.value);
			for(const auto byte : bytes) {
				bytecode.push_back(byte);
			}
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const Byte & args,
			const AddressTable &) {
			bytecode.push_back(args.value);
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const Uint64_BytexX & args,
			const AddressTable &) {
			const std::uint64_t count = args.bytes.size();
			const auto bytes = to_bytes(count);
			for(const auto byte : bytes) {
				bytecode.push_back(byte);
			}
			for(const auto byte : args.bytes) {
				bytecode.push_back(byte);
			}
		}



		void assemble_opcode(
			std::vector<std::uint8_t> & bytecode,
			const inst::ExecInst & inst,
			const AddressTable &) {
			bytecode.push_back(static_cast<std::uint8_t>(inst.get_opcode()));
		}
		void assemble_opcode(
			std::vector<std::uint8_t> &,
			const inst::Label &,
			const AddressTable &) {}
	}



	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Instruction> & instructions,
		const AddressTable & jump_table,
		const std::unordered_map<std::string, std::uint64_t> & fx_table) {
		
		std::vector<std::uint8_t> bytecode;
		bytecode.push_back(ltn::major_version);
		

		bytecode += to_bytes(std::size_t(std::size(fx_table)));
		for (const auto & [name, addr] : fx_table) {
			bytecode += to_bytes(std::uint64_t(std::size(name)));
			bytecode += std::vector<std::uint8_t> {std::begin(name), std::end(name)};
			bytecode += to_bytes(std::uint64_t(addr));
		}

		for(const auto & inst : instructions) {
			if(auto executable = inst.as<inst::ExecInst>()) {
				assemble_opcode(bytecode, *executable, jump_table);
			}
			else if(auto label = inst.as<inst::Label>()) {
				assemble_opcode(bytecode, *label, jump_table);
			}

			const auto args = inst.args();
			std::visit([&jump_table, &bytecode] (auto & args) {
				return assemble_args(bytecode, args, jump_table);
			}, args);
		}

		return bytecode;
	}
}