#pragma once
#include "Object.hxx"

namespace ltn::vm {
	struct Plugin : Object {
		void * handle;
		void(*gc_mark)(void);
	};
}