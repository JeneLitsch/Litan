#include "Function.hxx"
#include "ltnc/ast/stmt/Statement.hxx"

namespace ltn::c::ast::decl {
	Except::Except(
		const std::string & errorname,
		stmt_ptr && body,
		const SourceLocation & location)
		: Node(location)
		, body(std::move(body))
		, errorname(errorname) {}

	Except::~Except() {}

	Function::Function(
		const std::string & name,
		Namespace namespaze,
		Parameters parameters,
		stmt_ptr body,
		const SourceLocation & location)
		: Declaration(location, name, namespaze)
		, parameters(std::move(parameters))
		, body{std::move(body)} {}

	Function::~Function() {}
}