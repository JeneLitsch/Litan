#include "LtncEvaluator.hxx"

std::optional<ltnc::ExprInfo> ltnc::Evaluator::optimize(
	const ExprInfo & l,
	const ExprInfo & r) const {

	if(l.constant && r.constant) {
		
		if(l.typeId == TypeId("int")) {
			std::int64_t value = this->eval(
				std::get<std::int64_t>(l.constant->value),
				std::get<std::int64_t>(r.constant->value));
			Constant constant(value);
			CodeBuffer code(false);
			code << AssemblyCode("newi " + std::to_string(value));
			return ExprInfo(l.typeId, code, constant);
		}

		if(l.typeId == TypeId("flt")) {
			double value = this->eval(
				std::get<double>(l.constant->value),
				std::get<double>(r.constant->value));
			Constant constant(value);
			CodeBuffer code(false);
			code << AssemblyCode("newf " + std::to_string(value));
			return ExprInfo(l.typeId,  code, constant);
		}
	}
	return {};
}
