#pragma once
#include <chrono>
namespace ltn::vm {
	class Clock {
	public:
		Clock();
		double getSeconds() const;
	private:
		std::chrono::steady_clock clock;
		std::chrono::time_point<std::chrono::steady_clock> start;
	};}