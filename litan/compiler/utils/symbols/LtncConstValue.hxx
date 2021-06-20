#pragma once
#include <cstdint>
#include <variant>
namespace ltnc {
	struct ConstValue {
		ConstValue(std::int64_t value) : value(value) {}
		ConstValue(double value) : value(value) {}		
		const std::variant<std::int64_t, double> value;
	};
}