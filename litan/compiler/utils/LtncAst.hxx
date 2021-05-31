#pragma once
#include "LtncDecl.hxx"
#include "LtncStmt.hxx"
#include "LtncExpr.hxx"

namespace ltnc {

	struct Program {
		std::vector<std::shared_ptr<DeclFunction>> functions;
		std::vector<Type> types;
		virtual ~Program() = default;
	};
}