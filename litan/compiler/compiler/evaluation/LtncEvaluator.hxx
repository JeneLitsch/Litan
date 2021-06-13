#pragma once
#include <cstdint>
#include <optional>
#include "LtncExprInfo.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncAssemblyCode.hxx"
namespace ltnc {
	// Base class for binary operator 
	class Evaluator {
	public:
		std::optional<ExprInfo> optimize(const ExprInfo & l, const ExprInfo & r) const;
	protected:
		virtual double eval(double a, double b) const = 0;
		virtual std::int64_t eval(std::int64_t a, std::int64_t b) const = 0;
	};
}