#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	std::string parse_special_member(Tokens & tokens) {
		return "special:" + parse_variable_name(tokens);
	}
}