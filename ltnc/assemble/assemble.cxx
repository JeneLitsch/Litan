#include "assemble.hxx"
#include "stdxx/casting.hxx"
#include "stdxx/array.hxx"
#include <iostream>
#include "ltn/version.hxx"
#include "ltn/file/FunctionPool.hxx"
#include "ltn/file/StringPool.hxx"
#include "ltn/file/binary.hxx"

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
			const LinkInfo &) {
		}

		void assemble_args(
			std::vector<std::uint8_t> &,
			const inst::InstNone &,
			const LinkInfo &) {
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstUint64 & args,
			const LinkInfo &) {
			bytecode += to_bytes(args.value);
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstUint16 & args,
			const LinkInfo &) {
			bytecode += to_bytes(args.value);
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstJump & args,
			const LinkInfo & link_info) {
			const auto address = resolve_label(link_info.jump_table, args.label);
			bytecode += to_bytes(address);
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstCall & args,
			const LinkInfo & link_info) {
			const auto index = link_info.function_pool.find_by_name(args.label);
			if(!index) throw std::runtime_error{"Cannot find function " + std::string{args.label}};
			write_u64(*index, bytecode);
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstInt64 & args,
			const LinkInfo &) {
			bytecode += to_bytes(args.value);
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstFloat & args,
			const LinkInfo &) {
			bytecode += to_bytes(args.value);
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstByte & args,
			const LinkInfo &) {
			bytecode += args.value;
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstUint64Bytex & args,
			const LinkInfo &) {
			const std::uint64_t count = args.bytes.size();
			bytecode += to_bytes(count);
			bytecode += args.bytes;
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstBytex0 & args,
			const LinkInfo &) {
			bytecode += args.bytes;
			bytecode.push_back(0); // Add null terminator
		}

		void assemble_args(
			std::vector<std::uint8_t> & bytecode,
			const inst::InstStringConstant & args,
			const LinkInfo & link_info) {
			if(std::optional<std::uint64_t> id = link_info.string_pool.find(args.label)) {
				bytecode += to_bytes(*id);
			}
			else {
				throw std::runtime_error{"Missing entry in StringPool: " + args.label};
			}
		}



		void assemble_opcode(
			std::vector<std::uint8_t> & bytecode,
			const auto & inst) {
			bytecode.push_back(static_cast<std::uint8_t>(inst.opcode));
		}

		void assemble_opcode(
			std::vector<std::uint8_t> &,
			const inst::InstLabel &) {
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
	}



	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Inst> & instructions,
		const LinkInfo & link_info) {
		
		std::vector<std::uint8_t> bytecode;
		bytecode.push_back(ltn::major_version);

		link_info.function_pool.write(bytecode);
		link_info.string_pool.write(bytecode);
		bytecode += sequence_table(link_info.global_table);
		bytecode += sequence_table(link_info.member_name_table);

		for(const auto & inst : instructions) {
			std::visit([&] (auto & i) {
				return assemble_opcode(bytecode, i);
			}, inst);

			std::visit([&] (auto & i) {
				return assemble_args(bytecode, i, link_info);
			}, inst);
		}

		return bytecode;
	}


}