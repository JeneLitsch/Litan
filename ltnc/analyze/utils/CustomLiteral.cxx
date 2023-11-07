#include "CustomLiteral.hxx"
#include "ltnc/sst/expr/Literal.hxx"


namespace ltn::c {
	sst::expr_ptr CustomLiteral::operator()(const std::string & value) const {
		return this->fx(value);
	}
	
	
	
	const std::string & CustomLiteral::get_type() const {
		return this->type;
	}



	sst::expr_ptr CustomLiteral::make(const std::string & str) {
		return std::make_unique<sst::String>(str);
	}



	sst::expr_ptr CustomLiteral::make(double value) {
		return std::make_unique<sst::Float>(value);

	}



	sst::expr_ptr CustomLiteral::make(std::int64_t value) {
		return std::make_unique<sst::Integer>(value);
	}
}