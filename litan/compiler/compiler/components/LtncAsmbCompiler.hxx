#pragma once
#include "LtncStmt.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncCodeBuffer.hxx"
namespace ltnc {
	class AsmbCompiler {
	public:
		CodeBuffer compile(CompilerPack & compPkg, const std::shared_ptr<StmtAsm> & stmt) const;
	};
}