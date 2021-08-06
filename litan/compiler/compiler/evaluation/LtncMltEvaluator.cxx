#include "LtncMltEvaluator.hxx"

double ltnc::MltEvaluator::eval(double a, double b) const {
	return a * b;
}

std::int64_t ltnc::MltEvaluator::eval(std::int64_t a, std::int64_t b) const {
	return a * b;
}