#include "LtncSubEvaluator.hxx"

double ltn::c::SubEvaluator::eval(double a, double b) const {
	return a - b;
}

std::int64_t ltn::c::SubEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a - b;
}