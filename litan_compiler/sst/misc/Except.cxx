#include "Except.hxx"
#include "litan_compiler/sst/stmt/Statement.hxx"

namespace ltn::c::sst::misc {
	Except::Except(const std::string & errorname, stmt_ptr body)
		: body(std::move(body))
		, errorname(errorname) {}



	Except::~Except() {}



	std::unique_ptr<Except> except(const std::string & errorname, stmt_ptr body) {
		return std::make_unique<Except>(errorname, std::move(body));
	}
}