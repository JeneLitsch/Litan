#include "Enumeration.hxx"

namespace ltn::c::ast::decl {
	Enumeration::Enumeration(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze,
		std::vector<Label> labels)
		: Declaration(location, name, namespaze)
		, labels{std::move(labels)} {}



	Enumeration::~Enumeration() {}




	std::unique_ptr<Enumeration> enumeration(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze,
		std::vector<Enumeration::Label> labels) {
		
		return std::make_unique<Enumeration>(location, name, namespaze, std::move(labels));
	}
}