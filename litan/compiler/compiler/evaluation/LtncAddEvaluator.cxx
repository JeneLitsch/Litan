#include "LtncAddEvaluator.hxx"

double ltnc::AddEvaluator::eval(double a, double b) const {
	return a + b;
};

std::int64_t ltnc::AddEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a + b;
};