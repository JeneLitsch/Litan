#pragma once
#include "LtncAddEvaluator.hxx"
namespace ltn::c {
	class SubEvaluator : public Evaluator {
	protected:
		virtual double eval(double a, double b) const override;
		virtual std::int64_t eval(std::int64_t a, std::int64_t b) const override;
	};
}