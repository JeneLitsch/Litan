#include "Label.hxx"
#include <sstream>
#include "ltnc/type/to_string.hxx"

namespace ltn::c {
	const std::string & Label::get_name() const {
		return this->name;
	} 


	std::string replace(
		std::string str,
		const std::string & find,
		const std::string & replace) {
		std::size_t pos = 0;
		while ((pos = str.find(find, pos)) != std::string::npos) {
			str.replace(pos, std::size(find), replace);
			pos += std::size(replace);
		}
		return str;
	}


	std::string Label::mangle() const {
		auto str = this->get_name();
		str = replace(str, "::", "_");
		str = replace(str, "(", "_");
		str = replace(str, ")", "");
		return "fx_" + str;
	}



	std::string Label::to_string() const {
		switch (this->use_case) {
			case UseCase::EXTERNAL: return this->get_name();
			case UseCase::INTERNAL: return "_" + this->get_name();
		}
		throw std::runtime_error{"Invalid Label::UseCase"};
	}
}