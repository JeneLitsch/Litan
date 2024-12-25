#include "FxPointer.hxx"

namespace ltn::c::ast::expr {
	FxPointer::FxPointer(
		const std::string & name,
		const Namespace & namespaze,
		std::uint64_t placeholders,
		bool is_variadic,
		const SourceLocation & location)
		: Expression(location)
		, name(name)
		, namespaze(namespaze)
		, placeholders(placeholders)
		, is_variadic{is_variadic} {}
	


	void FxPointer::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}

	
	
	std::uint64_t FxPointer::arity() const {
		return this->placeholders;
	}



	std::unique_ptr<FxPointer> fx_pointer(
		const SourceLocation & location, 
		const std::string & name,
		const Namespace & namespaze,
		std::uint64_t placeholders,
		bool is_variadic) {
		
		return std::make_unique<FxPointer>(name, namespaze, placeholders, is_variadic, location);
	}
}