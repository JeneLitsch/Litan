#pragma once

namespace ltn::c::type {
	class Type;
	struct Integer {
		static bool is_assignable_from(const Type & type);
	};
}