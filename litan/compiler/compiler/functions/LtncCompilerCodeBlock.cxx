#include "LtncCompilerFunctions.hxx"
#include "LtnErrorReporter.hxx"

ltn::c::StmtInfo ltn::c::compile::codeBlock(
	CompilerPack & compPkg,
	const StmtBlock & block) {

	CodeBuffer code = compPkg.codeBuffer();
	ltn::ErrorReporter errorReporter;
	unsigned stackalloc = 0;
	unsigned varCount = 0;

	auto compileStatement = [&code, &compPkg, &stackalloc](const Stmt & stmt) {
		StmtInfo stmtInfo = statement(compPkg, stmt);
		stackalloc = std::max<unsigned>(stackalloc, stmtInfo.stackalloc);
		code << stmtInfo.code;
	};

	compPkg.getSymbolTable().addBlockScope();
	for(const auto & stmt : block.statements) {
		try {
			if(const auto * var = dynamic_cast<const StmtVar*>(stmt.get())) {
				compPkg.getSymbolTable().match(var->debugInfo, var->typeId);
				compPkg.getSymbolTable().insert(var->debugInfo, var->varId, var->typeId);
				varCount++;
				if(var->typeId == TVoid) {
					throw error::voidVariable(var->debugInfo, var->varId);
				}
				if(var->assign)  {
					compileStatement(*var->assign);
				}
			}
			else {
				compileStatement(*stmt);
			}
		}
		catch(const ltn::Error & error) {
			errorReporter << error;
		}
	}
	if(errorReporter.throwable()) {
		throw errorReporter;
	}
	stackalloc += varCount;
	compPkg.getSymbolTable().remove();
	return StmtInfo(code, stackalloc);
}