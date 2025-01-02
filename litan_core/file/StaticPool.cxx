#include "StaticPool.hxx"
#include "binary.hxx"

namespace ltn {
	void StaticPool::read(std::span<const std::uint8_t>::iterator & it) {
		const std::uint64_t size = read_u64(it);
		for(std::uint64_t i = 0; i < size; i++) {
			std::uint64_t id = read_u64(it);
			std::string name;
			while(char c = static_cast<char>(read_u8(it))) {
				name.push_back(c);
			}
			this->name_to_address[name] = id;
		}
	}



	void StaticPool::write(std::vector<std::uint8_t> & bytecode) const {
		write_u64(this->name_to_address.size(), bytecode);
		for(const auto & [name, id] : this->name_to_address) {
			write_u64(id, bytecode);
			for(char c : name) {
				write_u8(static_cast<std::uint8_t>(c), bytecode);
			}
			write_u8(0, bytecode); // Null terminator
		}
	}



	void StaticPool::insert(std::uint64_t id, std::string str) {
		this->name_to_address[str] = id;
	}
	
	
	
	std::optional<std::uint64_t> StaticPool::at(std::string str) const {
		if(this->name_to_address.contains(str)) {
			return this->name_to_address.at(str);
		}
		else {
			return std::nullopt;
		}

	}
}