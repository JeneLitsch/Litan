#pragma once
#include <map>
#include <memory>
#include <vector>
#include <cstdint>

#include "ltnvm/objects/Type.hxx"

namespace ltn::vm {
	class TypeTable {
	public:
		const Type * operator[](std::uint64_t id) const;
		std::uint64_t add(const std::vector<std::uint8_t> & code, std::unique_ptr<Type> type);
		std::uint64_t resolve(const std::vector<std::uint8_t> & code) const;
		std::pair<std::uint64_t, const std::uint8_t *> make(const std::uint8_t * code);
		bool contains(const std::vector<std::uint8_t> & code) const;

	private:
		std::vector<std::unique_ptr<Type>> types;
		std::map<std::vector<std::uint8_t>, std::uint64_t> code_to_id;
	};
}