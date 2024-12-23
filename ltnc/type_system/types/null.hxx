#pragma once

namespace ltn::c::type {
	class Type;
	struct Null {
		static bool is_assignable_from(const Type & type);
	};
}