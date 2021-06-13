#pragma once
#include "LtncCompilerComponent.hxx"
#include "LtncStmt.hxx"
namespace ltnc {
	class AsmbCompiler : public CompilerComponent<CodeBuffer, StmtAsm> {
	public:
		virtual CodeBuffer compile(CompilerPack & compPkg, const std::shared_ptr<StmtAsm> & stmt) const override;
	};
}