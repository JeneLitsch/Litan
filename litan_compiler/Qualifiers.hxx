#pragma once

namespace ltn::c {
	struct Qualifiers {
		bool is_const = false;
		bool is_extern = false;
		bool is_private = false;
		bool is_coroutine = false;
		
		static const Qualifiers none;
		static const Qualifiers just_const;
	};
}