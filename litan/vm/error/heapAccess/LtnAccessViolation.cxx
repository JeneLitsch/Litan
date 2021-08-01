#include "LtnAccessViolation.hxx"


ltn::AccessViolation::AccessViolation(
	const std::string & msg,
	std::uint64_t ptr,
	std::uint64_t idx,
	const std::string & type) 
:	RuntimeError(msg), ptr(ptr), idx(idx), type(type) {}

std::uint64_t ltn::AccessViolation::getPtr() const {
	return this->ptr;
}

std::uint64_t ltn::AccessViolation::getIdx() const {
	return this->idx;
}
