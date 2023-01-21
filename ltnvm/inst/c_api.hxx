#pragma once
#include "ltnvm/external/Parameters.hxx"

namespace ltn::vm {
	struct CoreWrapper {
		ext::Parameters params;
		Value return_value = value::null;
	};

	CApi bind_api(CoreWrapper & wrapper);
}