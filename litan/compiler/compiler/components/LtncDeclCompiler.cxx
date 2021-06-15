#include "LtncDeclCompiler.hxx"
#include "Unused.hxx"
ltnc::DeclCompiler::DeclCompiler(StmtCompiler & stmtCompiler)
	: stmtCompiler(stmtCompiler) {}

ltnc::StmtInfo ltnc::DeclCompiler::compile(
	CompilerPack & compPkg,
	const std::shared_ptr<DeclFunction> & decl) const {
		
	const Func & func = compPkg.getSymbolTable().match(decl->signature);
	compPkg.getSymbolTable().match(decl->signature.returnType);
	compPkg.getSymbolTable().addFunctionScope(func.signature);
	
	// register parameter
	for(const Param & param : decl->signature.params) {
		compPkg.getSymbolTable().match(param.typeId);
		compPkg.getSymbolTable().insert(param.name, TypeId(param.typeId));
	}
	// eval body
	StmtInfo body = stmtCompiler.compileStmt(compPkg, decl->body);

	// create code;
	CodeBuffer code = compPkg.codeBuffer();
	code << Comment(this->fxComment(decl));
	code << AssemblyCode("-> " + func.jumpMark);
	// load params into memory (backwards because LIFO)
	const auto & params = decl->signature.params; 
	code << AssemblyCode("stackalloc " + std::to_string(body.stackalloc + params.size()));
	for(auto param = params.rbegin(); param != params.rend(); ++param) {
		// store parameter;
		std::uint64_t varAddr = compPkg.getSymbolTable().match((*param).name).addr;
		code << Inst::store(static_cast<std::uint32_t>(varAddr));
	}
	code << body.code;
	code << AssemblyCode("\n");
	compPkg.getSymbolTable().remove();
	return StmtInfo(code, 0);
}



std::string ltnc::DeclCompiler::fxComment(
	const std::shared_ptr<DeclFunction> & decl) const {

	
	std::string text;
	text += decl->signature.name + " ( ";
	for (const auto & param : decl->signature.params) {
		text += param.typeId.name + " ";
	}
	text += "-> ";
	text += decl->signature.returnType.name + " ) ";
	text += "[ ";
	if (decl->inlined) {
		text += "inline ";
	}
	text += "]";
	return text;
}