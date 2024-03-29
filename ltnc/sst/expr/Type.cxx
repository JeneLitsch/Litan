#include "Type.hxx"

namespace ltn::c::sst::expr {
	Type::Type(std::vector<std::uint8_t> type_code)
		: type_code{std::move(type_code)} {}

	std::uint64_t Type::alloc() const {
		return 0;
	}



	std::unique_ptr<Type> type(std::vector<std::uint8_t> code) {
		return std::make_unique<Type>(std::move(code));
	}
}