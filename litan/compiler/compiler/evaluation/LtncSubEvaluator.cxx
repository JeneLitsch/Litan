#include "LtncSubEvaluator.hxx"

double ltnc::SubEvaluator::eval(double a, double b) const {
	return a - b;
}

std::int64_t ltnc::SubEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a - b;
}