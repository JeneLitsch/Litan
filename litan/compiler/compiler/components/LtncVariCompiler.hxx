#pragma once
#include "LtncCompilerComponent.hxx"
#include "LtncExpr.hxx"
#include "LtncExprInfo.hxx"
namespace ltnc {
	class VariCompiler {
	public:
		ExprInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprVar> & access,
			const std::optional<ExprInfo> & expr) const;
	
	};
}