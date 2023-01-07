#include "Parameters.hxx"

namespace ltn::vm::ext {
	Parameters::Parameters(
		Heap & heap,
		const std::vector<Value> & params) 
		: heap(heap)
		, params(params) {}

	Parameters::~Parameters() {}
}

