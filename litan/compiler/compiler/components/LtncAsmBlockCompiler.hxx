#pragma once
#include "LtncCompilerComponent.hxx"
#include "LtncStmt.hxx"
namespace ltnc {
	class AsmBlockCompiler : public CompilerComponent<std::string, StmtAsm> {
	public:
		virtual std::string compile(CompilerPack & compPkg, const std::shared_ptr<StmtAsm> & stmt) const override;
	};
}