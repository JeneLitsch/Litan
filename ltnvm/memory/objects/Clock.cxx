#include "Clock.hxx"

ltn::vm::Clock::Clock() {
	this->start = this->clock.now();

}



stx::float64_t ltn::vm::Clock::getSeconds() const {
	const auto now = this->clock.now();
	const std::chrono::duration<stx::float64_t> duration = now - this->start;
	return duration.count();
}