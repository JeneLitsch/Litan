#include "MemberNameTable.hxx"
#include "binary.hxx"

namespace ltn {
	void MemberNameTable::read(std::span<const std::uint8_t>::iterator & it) {
		const std::uint64_t size = read_u64(it);
		for(std::uint64_t i = 0; i < size; i++) {
			std::uint64_t id = read_u64(it);
			std::string name;
			while(char c = static_cast<char>(read_u8(it))) {
				name.push_back(c);
			}
			this->id_to_name[id] = name;
		}
	}



	void MemberNameTable::write(std::vector<std::uint8_t> & bytecode) const {
		write_u64(this->id_to_name.size(), bytecode);
		for(const auto & [id, name] : this->id_to_name) {
			write_u64(id, bytecode);
			for(char c : name) {
				write_u8(static_cast<std::uint8_t>(c), bytecode);
			}
			write_u8(0, bytecode); // Null terminator
		}
	}


	void MemberNameTable::insert(std::uint64_t id, std::string str) {
		this->id_to_name[id] = str;
	}



	std::optional<std::string_view> MemberNameTable::at(const std::uint64_t id) const {
		if(this->id_to_name.contains(id)) {
			return this->id_to_name.at(id);
		}
		else {
			return std::nullopt;
		}
	}
}