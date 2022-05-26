#pragma once
#include <vector>
#include <cstdint>
#include <istream>

namespace ltn::a {
	class Ltna {
	public:
		std::vector<std::uint8_t> process(std::istream & in) const;
	private:

	};
}