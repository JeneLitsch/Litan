#pragma once
#include <vector>
#include <cstdint>

namespace ltn::vm {
	class Register {
	public:
		std::uint64_t popU();
		std::int64_t popI();
		double popF();

		void pushU(std::uint64_t value);
		void pushI(std::int64_t value);
		void pushF(double value);
	private:
		std::vector<std::uint64_t> stack;
	};
}