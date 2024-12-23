#pragma once

namespace ltn::c::type {
	class Type;
	struct Floating {
		static bool is_assignable_from(const Type & type);
	};
}