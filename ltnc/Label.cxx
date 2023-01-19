#include "Label.hxx"
#include <sstream>
#include "ltnc/type/to_string.hxx"

namespace ltn::c {
	const std::string & Label::get_name() const {
		return this->name;
	} 


	std::string Label::to_string() const {
		switch (this->use_case) {
			case UseCase::EXTERNAL: return this->get_name();
			case UseCase::INTERNAL: return "_" + this->get_name();
		}
		throw std::runtime_error{"Invalid Label::UseCase"};
	}
}