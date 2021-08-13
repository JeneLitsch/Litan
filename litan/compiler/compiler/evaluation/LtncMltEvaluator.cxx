#include "LtncMltEvaluator.hxx"

double ltn::c::MltEvaluator::eval(double a, double b) const {
	return a * b;
}

std::int64_t ltn::c::MltEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a * b;
}