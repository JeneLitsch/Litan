#include "LtncAddEvaluator.hxx"

double ltn::c::AddEvaluator::eval(double a, double b) const {
	return a + b;
}

std::int64_t ltn::c::AddEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a + b;
}