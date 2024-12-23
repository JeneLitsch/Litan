#pragma once

namespace ltn::c::type {
	class Type;
	struct Any {
		static bool is_assignable_from(const Type & type);
	};
}