#include "CustomLiteral.hxx"
#include "litan_compiler/sst/expr/Literal.hxx"
#include "litan_compiler/sst/expr/Var.hxx"

namespace ltn::c {
	sst::expr_ptr CustomLiteral::operator()(const std::string & value) const {
		return this->fx(value);
	}
	
	
	
	const std::string & CustomLiteral::get_type() const {
		return this->type;
	}



	sst::expr_ptr CustomLiteral::make(const std::string & str) {
		return sst::expr::string(str);
	}



	sst::expr_ptr CustomLiteral::make(double value) {
		return sst::expr::floating(value);

	}



	sst::expr_ptr CustomLiteral::make(std::int64_t value) {
		return sst::expr::integer(value);
	}
}