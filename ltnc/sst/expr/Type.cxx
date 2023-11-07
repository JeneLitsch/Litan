#include "Type.hxx"

namespace ltn::c::sst {
	Type::Type(std::vector<std::uint8_t> type_code)
		: type_code{std::move(type_code)} {}

	std::uint64_t Type::alloc() const {
		return 0;
	}
}