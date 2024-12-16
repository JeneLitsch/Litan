#include "StringPool.hxx"
#include "ltn/header.hxx"
#include <algorithm>

namespace ltn {
	void StringPool::read(std::span<const std::uint8_t>::iterator & it) {
		const std::uint64_t size = read_u64(it);
		for(std::uint64_t i = 0; i < size; i++) {
			this->data.push_back("");
			while(char c = static_cast<char>(read_u8(it))) {
				this->data.back().push_back(c);
			}
		}
	}



	void StringPool::write(std::vector<std::uint8_t> & bytecode) const {
		write_u64(this->data.size(), bytecode);
		for(const std::string & str : this->data) {
			for(char c : str) {
				write_u8(static_cast<std::uint8_t>(c), bytecode);
			}
			write_u8(0, bytecode); // Null terminator
		}
	}



	std::uint64_t StringPool::push(std::string str) {
		if(std::optional<std::uint64_t> id = find(str)) {
			return *id;
		}
		else {
			this->data.push_back(std::move(str));
			return this->size() - 1;
		}
	}



	std::optional<std::uint64_t> StringPool::find(const std::string_view str) const {
		const auto begin = std::begin(this->data);
		const auto end = std::end(this->data);
		const auto pos = std::find(begin, end, str);
		if(pos != end) {
			return std::distance(begin, pos);
		}
		else {
			return std::nullopt;
		}
	}



	std::uint64_t StringPool::size() const{
		return this->data.size();
	}



	std::string_view StringPool::operator[](std::uint64_t i) const{
		return this->data.at(i);
	}
}