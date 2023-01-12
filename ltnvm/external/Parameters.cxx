#include "Parameters.hxx"

namespace ltn::vm::ext {
	Parameters::Parameters(
		Heap & heap,
		const Array & params) 
		: heap(heap)
		, params(params) {}

	Parameters::~Parameters() {}
}

