#include "LtncDivEvaluator.hxx"

double ltnc::DivEvaluator::eval(double a, double b) const {
	return a / b;
};

std::int64_t ltnc::DivEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a / b;
};