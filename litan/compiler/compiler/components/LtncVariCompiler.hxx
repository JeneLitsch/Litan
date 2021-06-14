#pragma once
#include "LtncExpr.hxx"
#include "LtncExprInfo.hxx"
#include "LtncCompilerPack.hxx"
namespace ltnc {
	class VariCompiler {
	public:
		ExprInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprVar> & access,
			const std::optional<ExprInfo> & expr) const;
	
	};
}