#pragma once
#include <chrono>
#include <string_view>
#include "ltn/float64_t.hxx"
namespace ltn::vm {
	class Clock {
	public:
		constexpr static std::string_view typeName = "Clock";
		
		Clock();

		stx::float64_t getSeconds() const;

		auto clone() const {
			return *this;
		}

	private:
		std::chrono::steady_clock clock;
		std::chrono::time_point<std::chrono::steady_clock> start;
	};}