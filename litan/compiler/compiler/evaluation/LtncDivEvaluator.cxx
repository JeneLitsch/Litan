#include "LtncDivEvaluator.hxx"

double ltn::c::DivEvaluator::eval(double a, double b) const {
	return a / b;
}

std::int64_t ltn::c::DivEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a / b;
}