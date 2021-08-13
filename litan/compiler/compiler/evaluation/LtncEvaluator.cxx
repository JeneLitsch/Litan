#include "LtncEvaluator.hxx"
#include "LtncBaseTypes.hxx"
std::optional<ltn::c::ExprInfo> ltn::c::Evaluator::optimize(
	const ExprInfo & l,
	const ExprInfo & r) const {

	if(l.constValue && r.constValue) {
		
		if(l.typeId == TypeId(TInt)) {
			std::int64_t value = this->eval(
				std::get<std::int64_t>(l.constValue->value),
				std::get<std::int64_t>(r.constValue->value));
			ConstValue constValue(value);
			CodeBuffer code(false);
			code << AssemblyCode("newi " + std::to_string(value));
			return ExprInfo(l.typeId, code, constValue);
		}

		if(l.typeId == TypeId(TFloat)) {
			double value = this->eval(
				std::get<double>(l.constValue->value),
				std::get<double>(r.constValue->value));
			ConstValue constValue(value);
			CodeBuffer code(false);
			code << AssemblyCode("newf " + std::to_string(value));
			return ExprInfo(l.typeId,  code, constValue);
		}
	}
	return {};
}
