#pragma once
#include <chrono>
#include <string_view>
#include "stdxx/float64_t.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	class Clock : public Object {
	public:
		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;
		virtual Value get_member(std::uint64_t id) const override;
		constexpr static std::string_view typeName = "Clock";
		
		Clock();

		stx::float64_t getSeconds() const;


	private:
		std::chrono::steady_clock clock;
		std::chrono::time_point<std::chrono::steady_clock> start;
	};



	inline Clock clone(const Clock & clock) {
		return clock;
	}
}