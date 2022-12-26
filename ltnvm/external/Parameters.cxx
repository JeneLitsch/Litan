#include "Parameters.hxx"

namespace ltn::vm::ext {
	Parameters::Parameters(
		Heap & heap,
		Register & reg,
		const std::vector<Value> & params) 
		: heap(heap)
		, reg(reg)
		, params(params) {}

	Parameters::~Parameters() {}
}

