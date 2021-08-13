#include "LtncModEvaluator.hxx"

double ltn::c::ModEvaluator::eval(double a, double b) const {
	return a + b;
}

std::int64_t ltn::c::ModEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a + b;
}