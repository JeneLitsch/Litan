#include "LtncModEvaluator.hxx"

double ltnc::ModEvaluator::eval(double a, double b) const {
	return a + b;
};

std::int64_t ltnc::ModEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a + b;
};