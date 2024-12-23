#pragma once

namespace ltn::c::type {
	class Type;
	struct Boolean {
		static bool is_assignable_from(const Type & type);
	};
}