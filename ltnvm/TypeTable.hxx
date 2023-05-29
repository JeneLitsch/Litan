#pragma once
#include <map>
#include <memory>
#include <vector>
#include <cstdint>

#include "ltnvm/objects/Type.hxx"

namespace ltn::vm {
	class TypeTable {
	public:
		std::map<std::vector<std::uint8_t>, std::uint64_t> code_to_id;
		const TypeNode * operator[](std::uint64_t id) const;
		std::uint64_t size() const;
		void add(std::unique_ptr<TypeNode> type);
		std::uint64_t resolve_code(const std::vector<std::uint8_t> & code) const;

		std::pair<std::uint64_t, const std::uint8_t *> make(const std::uint8_t * code);
		
	private:
		std::vector<std::unique_ptr<TypeNode>> types;
	};
}