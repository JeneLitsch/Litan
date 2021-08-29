#pragma once
#include "LtncDecl.hxx"
#include "LtncStmt.hxx"
#include "LtncExpr.hxx"

namespace ltn::c {

	struct Program {
		std::vector<std::unique_ptr<DeclTemplateFunction>> functionTemplates;
		std::vector<std::unique_ptr<DeclTemplateStruct>> structTemplates;
		std::vector<std::unique_ptr<DeclFunction>> functions;
		std::vector<std::unique_ptr<DeclStruct>> structs;
		std::vector<std::unique_ptr<Type>> types;
		virtual ~Program() = default;
	};
}