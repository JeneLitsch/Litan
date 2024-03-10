#include "Parameters.hxx"

namespace ltn::vm::ext {
	Parameters::Parameters(
		Heap &,
		const std::vector<Value> & params) 
		: params(params) {}

	Parameters::~Parameters() {}
}

