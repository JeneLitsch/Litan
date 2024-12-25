#include "Plugin.hxx"
#ifdef __linux__
#include <dlfcn.h>
#endif

namespace ltn::vm {
#ifdef __linux__
	Plugin::~Plugin() {
		dlclose(this->handle);
	}
#else
	Plugin::~Plugin() {}
#endif
}