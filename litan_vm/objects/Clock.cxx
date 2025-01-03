#include "Clock.hxx"
#include "litan_vm/stdlib/chrono.hxx"

namespace ltn::vm {
	void Clock::stringify(VMCore &, std::ostream & oss, bool) {
		oss << "<clock: " << getSeconds() << "s>";
	}



	Value Clock::get_member(VMCore & core, std::uint64_t id) const {
		return core.types.clock.get_nonstatic_member(core, id);
	}



	ltn::vm::Clock::Clock() {
		this->start = this->clock.now();

	}



	stx::float64_t ltn::vm::Clock::getSeconds() const {
		const auto now = this->clock.now();
		const std::chrono::duration<stx::float64_t> duration = now - this->start;
		return duration.count();
	}
}