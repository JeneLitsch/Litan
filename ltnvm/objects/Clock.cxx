#include "Clock.hxx"
#include "ltnvm/stdlib/chrono.hxx"

namespace ltn::vm {
	void Clock::stringify(VMCore &, std::ostream & oss, bool) {
		oss << "<clock: " << getSeconds() << "s>";
	}



	Value Clock::get_member(std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::to_seconds>      (ReservedMemberCode::TO_SECONDS),
			wrap<stdlib::to_milliseconds> (ReservedMemberCode::TO_MILLISECONDS),
		};

		return search_native_function_table(native_function_table, id);
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