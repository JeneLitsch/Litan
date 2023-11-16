#pragma once
#include "Static.hxx"

namespace ltn::c::ast::decl {
	struct Definition final : public Static {
		Definition(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze);
		virtual ~Definition();
		ast::expr_ptr expr;
	};
}