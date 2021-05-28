#include "LtncEvaluator.hxx"

std::optional<ltnc::ExprInfo> ltnc::Evaluator::optimize(
	const ExprInfo & l,
	const ExprInfo & r) const {

	if(l.constant && r.constant) {
		if(l.type == Type::INT) {
			std::int64_t value = this->eval(
				std::get<std::int64_t>(l.constant->value),
				std::get<std::int64_t>(r.constant->value));
			Constant constant(value);
			return ExprInfo(l.type, "newi " + std::to_string(value) + "\n", constant);
		}
		if(l.type == Type::FLT) {
			double value = this->eval(
				std::get<double>(l.constant->value),
				std::get<double>(r.constant->value));
			Constant constant(value);
			return ExprInfo(l.type, "newf " + std::to_string(value) + "\n", constant);
		}
	}
	return {};
}
