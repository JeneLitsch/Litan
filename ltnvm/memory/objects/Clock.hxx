#pragma once
#include <chrono>
#include <string_view>
namespace ltn::vm {
	class Clock {
	public:
		Clock();
		double getSeconds() const;
		constexpr static std::string_view typeName = "Clock";
	private:
		std::chrono::steady_clock clock;
		std::chrono::time_point<std::chrono::steady_clock> start;
	};}