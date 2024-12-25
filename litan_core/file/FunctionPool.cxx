#include "FunctionPool.hxx"
#include "litan_core/header.hxx"
#include <iostream>
#include <bitset>



namespace ltn {
	const FunctionContext * FunctionPool::operator[](std::uint64_t id) const {
		return &this->entries[id];
	}



	std::optional<std::uint64_t> FunctionPool::find_by_name(const std::string_view name) const {
		auto * entry = this->get_by_name(name);
		return entry
			? std::optional<std::uint64_t>{std::distance(this->entries.data(), entry)}
			: std::nullopt;
	}
	
	
	
	const FunctionContext * FunctionPool::get_by_name(const std::string_view name) const {
		for(auto & entry : this->entries) {
			if(entry.name == name) {
				return &entry;
			}
		}
		return nullptr;
	}
	
	
	
	bool FunctionPool::contains(const std::string_view name) const {
		return get_by_name(name) != nullptr;
	}
	
	
	
	void FunctionPool::push_back(FunctionContext entry) {
		return this->entries.push_back(entry);
	}
	

	void FunctionPool::read(std::span<const std::uint8_t>::iterator & it) {
		const std::uint64_t table_size = read_u64(it);
		for(std::uint64_t i = 0; i < table_size; ++i) {
			
			const std::uint64_t name_size = read_u64(it);
			
			auto next = it + static_cast<long>(name_size);
			const std::string name { it, next };
			it = next;
			
			const std::uint8_t arity = read_u8(it);
			const std::uint64_t address = read_u64(it);
			const std::uint64_t frame_size = read_u64(it);
			const std::bitset<8> flags = read_u8(it);
			
			FunctionContext entry {
				.name = name,
				.arity = arity,
				.address = address,
				.frame_size = frame_size,
				.is_external = flags[0],
				.is_variadic = flags[1],
			};
			this->push_back(entry);
		}
	}



	void FunctionPool::write(std::vector<std::uint8_t> & bytecode) const {
		write_u64(std::size(this->entries), bytecode);
		for(auto & entry : this->entries) {
			write_u64(std::size(entry.name), bytecode);
			for(char c : entry.name) {
				write_u8(static_cast<std::uint8_t>(c), bytecode);
			}
			write_u8(entry.arity, bytecode);
			write_u64(entry.address, bytecode);
			write_u64(entry.frame_size, bytecode);
			
			std::bitset<8> flags;
			flags[0] = entry.is_external;	
			flags[1] = entry.is_variadic;	
			write_u8(static_cast<std::uint8_t>(flags.to_ullong()), bytecode);
		}
	}
}