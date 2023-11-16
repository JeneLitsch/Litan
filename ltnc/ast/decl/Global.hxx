#pragma once
#include "Static.hxx"

namespace ltn::c::ast::decl {
	struct Global final : Static {
		Global(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze);
		virtual ~Global();
		ast::expr_ptr expr;
	};
}