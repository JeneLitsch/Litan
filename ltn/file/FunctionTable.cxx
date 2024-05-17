#include "FunctionTable.hxx"
#include "ltn/header.hxx"

namespace ltn {
	FunctionTable::FunctionTable() {

	}
	
	
	
	const FunctionTable::Entry * FunctionTable::operator[](std::uint64_t id) const {
		return &this->entries[id];
	}
	
	
	
	const FunctionTable::Entry * FunctionTable::find_by_name(const std::string_view name) const {
		for(auto & entry : this->entries) {
			if(entry.name == name) {
				return &entry;
			}
		}
		return nullptr;
	}
	
	
	
	bool FunctionTable::contains(const std::string_view name) const {
		return find_by_name(name) != nullptr;
	}
	
	
	
	void FunctionTable::push_back(Entry entry) {
		return this->entries.push_back(entry);
	}
	
	
	
	FunctionTable::~FunctionTable() {

	}



	void FunctionTable::read(std::span<const std::uint8_t>::iterator & it) {
		const std::uint64_t table_size = read_u64(it);
		for(std::uint64_t i = 0; i < table_size; ++i) {
			const std::uint64_t name_size = read_u64(it);
			auto next = it + static_cast<long>(name_size);
			const std::string name { it, next };
			it = next;
			const std::uint64_t address = read_u64(it);
			this->push_back(FunctionTable::Entry{
				.address = address,
				.name = name, 
			});
		}
	}



	void FunctionTable::write(std::vector<std::uint8_t> & bytecode) const {
		write_u64(std::size(this->entries), bytecode);
		for(auto & entry : this->entries) {
			write_u64(std::size(entry.name), bytecode);
			for(char c : entry.name) {
				write_u8(static_cast<std::uint8_t>(c), bytecode);
			}
			write_u64(entry.address, bytecode);
		}
	}
}