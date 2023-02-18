#include "assemble.hxx"
#include "stdxx/casting.hxx"
#include "stdxx/array.hxx"
#include <iostream>
#include "ltn/version.hxx"

namespace ltn::c {
	std::uint64_t resolve_label(const AddressTable & jump_table, const std::string & label) {
		if(jump_table.contains(label)) return jump_table.at(label);
		else throw std::runtime_error{"Cannot find label " + label};
	}


	
	namespace {
		auto to_bytes(std::unsigned_integral auto value) {
			constexpr static auto SIZE = sizeof(value) / sizeof(std::uint8_t);
			std::array<std::uint8_t, SIZE> bytes;
			for(std::uint8_t & byte : bytes) {
				byte = static_cast<std::uint8_t>(value & 0xff);
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
			const inst::InstLabel &,
			const AddressTable &) {
		}
		void assemble_args(
			std::vector<std::uint8_t> &,
			const inst::InstNone &,
			const AddressTable &) {
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstUint64 & args,
			const AddressTable &) {
			bytecode += to_bytes(args.value);
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstUint16 & args,
			const AddressTable &) {
			bytecode += to_bytes(args.value);
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstJump & args,
			const AddressTable & jump_table) {
			const auto address = resolve_label(jump_table, args.label);
			bytecode += to_bytes(address);
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstCall & args,
			const AddressTable & jump_table) {
			const auto address = resolve_label(jump_table, args.label);
			bytecode += to_bytes(address);
			bytecode += args.arity;
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstJumpUint64 & args,
			const AddressTable & jump_table) {
			bytecode += to_bytes(resolve_label(jump_table, args.label));
			bytecode += to_bytes(args.value);
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstInt64 & args,
			const AddressTable &) {
			bytecode += to_bytes(args.value);
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstFloat & args,
			const AddressTable &) {
			bytecode += to_bytes(args.value);
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstByte & args,
			const AddressTable &) {
			bytecode += args.value;
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstUint64Bytex & args,
			const AddressTable &) {
			const std::uint64_t count = args.bytes.size();
			bytecode += to_bytes(count);
			bytecode += args.bytes;
		}
		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstBytex0 & args,
			const AddressTable &) {
			bytecode += args.bytes;
			bytecode.push_back(0); // Add null terminator
		}



		void assemble_opcode(
			std::vector<std::uint8_t> & bytecode,
			const auto & inst,
			const AddressTable &) {
			bytecode.push_back(static_cast<std::uint8_t>(inst.opcode));
		}
		void assemble_opcode(
			std::vector<std::uint8_t> &,
			const inst::InstLabel &,
			const AddressTable &) {
			
		}


		std::vector<std::uint8_t> sequence_table(const AddressTable & table) {
			std::vector<std::uint8_t> bytecode;
			bytecode += to_bytes(std::size_t(std::size(table)));
			for (const auto & [name, address] : table) {
				bytecode += to_bytes(std::uint64_t(std::size(name)));
				bytecode += std::vector<std::uint8_t> {std::begin(name), std::end(name)};
				bytecode += to_bytes(std::uint64_t(address));
			}
			return bytecode;
		}

		AddressTable build_fx_table(
			const std::set<std::string> & fx_ids,
			const AddressTable & jump_table) {
			
			AddressTable function_table;
			for(const auto & fx_id : fx_ids) {
				if(jump_table.contains(fx_id)) {
					function_table[fx_id] = jump_table.at(fx_id);
				}
			}
			return function_table;
		}
	}



	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Inst> & instructions,
		const LinkInfo & link_info) {
		
		const auto jump_table     = scan(instructions);
		const auto function_table = build_fx_table(link_info.init_functions, jump_table);
		const auto & static_table = link_info.global_table;

		std::vector<std::uint8_t> bytecode;
		bytecode.push_back(ltn::major_version);

		bytecode += sequence_table(function_table);
		bytecode += sequence_table(static_table);

		for(const auto & inst : instructions) {
			std::visit([&] (auto & i) {
				return assemble_opcode(bytecode, i, jump_table);
			}, inst);

			std::visit([&jump_table, &bytecode] (auto & i) {
				return assemble_args(bytecode, i, jump_table);
			}, inst);
		}

		return bytecode;
	}


}