#pragma once

#include <cstdint>

namespace ltn::c::sst {
	class Statement : public Node {
	public:
		Statement() {}

		virtual ~Statement() = default;

		virtual std::size_t nested_alloc() const = 0;
		virtual std::size_t direct_alloc() const = 0;
	};
}