#include "LtncDeclCompiler.hxx"

ltnc::DeclCompiler::DeclCompiler(StmtCompiler & stmtCompiler)
	: stmtCompiler(stmtCompiler) {}

ltnc::StmtInfo ltnc::DeclCompiler::compile(
	CompilerPack & compPkg,
	const std::shared_ptr<DeclFunction> & decl) const {
		
	FxInfo fxInfo = *compPkg.matchFunction(decl->signature);
	compPkg.getTypeTable().guardType(decl->signature.returnType.name);
	compPkg.getScopes().addFunctionScope(fxInfo.signature);
	
	// register parameter
	for(const Param & param : decl->signature.params) {
		compPkg.getTypeTable().guardType(param.type.name);
		compPkg.getScopes().get().registerVar(param.name, param.type.name);
	}
	// eval body
	StmtInfo body = stmtCompiler.compileStmt(compPkg, decl->body);

	// create code;
	std::string code;
	code += this->fxComment(compPkg, decl);
	code += "-> " + fxInfo.jumpMark + "\n";
	// load params into memory (backwards because LIFO)
	const auto & params = decl->signature.params; 
	code += "stackalloc " + std::to_string(body.stackalloc + params.size()) + "\n";
	for(auto param = params.rbegin(); param != params.rend(); ++param) {
		// store parameter;
		std::uint64_t varAddr = compPkg.getScopes().get().getVar((*param).name).addr;
		code += "store " + std::to_string(varAddr) + "\n";
	}
	code += body.code;
	code += "\n\n";
	compPkg.getScopes().remove();
	return StmtInfo(code, 0);
}



std::string ltnc::DeclCompiler::fxComment(
	CompilerPack & compPkg,
	const std::shared_ptr<DeclFunction> & decl) const {
	
	std::string text;
	text += decl->signature.name + " ( ";
	for (const auto & param : decl->signature.params) {
		text += param.type.name + " ";
	}
	text += "-> ";
	text += decl->signature.returnType.name + " ) ";
	text += "[ ";
	if (decl->inlined) {
		text += "inline ";
	}
	text += "]";
	return this->comment(compPkg, text);
}