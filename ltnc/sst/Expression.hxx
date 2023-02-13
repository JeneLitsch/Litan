#pragma once
#include <cstdint>
#include <memory>
#include "ltnc/type/Type.hxx"
#include "Node.hxx"

namespace ltn::c::sst {
	struct Expression : public Node {
		virtual ~Expression() = default;
		type::Type type;

		virtual std::uint64_t alloc() const = 0;
	protected:
		Expression(const type::Type & type)
			: type{type} {}
	};
	using expr_ptr = std::unique_ptr<Expression>;
}