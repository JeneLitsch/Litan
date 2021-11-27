#include "Clock.hxx"

ltn::vm::Clock::Clock() {
	this->start = this->clock.now();

}

double ltn::vm::Clock::getSeconds() const {
	const auto now = this->clock.now();
	const std::chrono::duration<double> duration = now - this->start;
	return duration.count();
}