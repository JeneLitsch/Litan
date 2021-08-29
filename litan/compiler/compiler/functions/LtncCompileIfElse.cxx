#include "LtncCompilerFunctions.hxx"

ltn::c::StmtInfo ltn::c::compile::ifElse(CompilerPack & compPkg, const StmtIf & stmt) {
	CodeBuffer code = compPkg.codeBuffer();

	// make jump marks
	std::string jmIf = compPkg.getSymbolTable().makeJumpMark("IF");
	std::string jmElse = compPkg.getSymbolTable().makeJumpMark("ELSE");
	std::string jmEnd = compPkg.getSymbolTable().makeJumpMark("END_IF");
	
	ExprInfo condition = expression(compPkg, *stmt.condition);
	StmtInfo codeIf = statement(compPkg, *stmt.stmtIf);
	unsigned stackalloc;

	// ifElse
	if(stmt.stmtElse) {
		StmtInfo codeElse = statement(compPkg, *stmt.stmtElse);
		stackalloc = std::max<unsigned>(codeIf.stackalloc, codeElse.stackalloc);
		
		code << condition.code;
		code << AssemblyCode("ifnx");
		code << AssemblyCode("goto " + jmIf);
		code << AssemblyCode("goto " + jmElse);
		
		code << AssemblyCode("-> " + jmIf);
		code << codeIf.code;
		code << AssemblyCode("goto " + jmEnd);
		
		code << AssemblyCode("-> " + jmElse);
		code << codeElse.code;
		code << AssemblyCode("goto " + jmEnd);
		
		code << AssemblyCode("-> " + jmEnd);		
	}

	// if
	else {
		stackalloc = codeIf.stackalloc;
		code << condition.code;
		code << AssemblyCode("ifnx");
		code << AssemblyCode("goto " + jmIf);
		code << AssemblyCode("goto " + jmEnd);
		
		code << AssemblyCode("-> " + jmIf);
		code << codeIf.code;
		code << AssemblyCode("goto " + jmEnd);
		
		code << AssemblyCode("-> " + jmEnd);
	}
	return StmtInfo(code, stackalloc);
}