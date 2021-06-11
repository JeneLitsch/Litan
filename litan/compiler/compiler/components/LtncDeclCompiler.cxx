#include "LtncDeclCompiler.hxx"

ltnc::DeclCompiler::DeclCompiler(StmtCompiler & stmtCompiler)
	: stmtCompiler(stmtCompiler) {}

ltnc::StmtInfo ltnc::DeclCompiler::compile(CompilerPack & compPkg, const std::shared_ptr<DeclFunction> & decl) const {
	FxInfo fxInfo = *compPkg.matchFunction(decl->signature);

	compPkg.getTypeTable().guardType(decl->signature.returnType);

	compPkg.getScopes().addFunctionScope(fxInfo.signature);
	// register parameter
	for(const Param & param : decl->signature.params) {
		// check existence of type
		compPkg.getTypeTable().guardType(param.type);
		// register var
		compPkg.getScopes().get().registerVar(param.name, param.type);
	}
	// eval body
	StmtInfo body = stmtCompiler.compileStmt(compPkg, decl->body);

	// create code;
	std::string code;
	code += this->comment(compPkg, decl->signature.name + " " + std::to_string(decl->signature.params.size()) + " -> " + decl->signature.returnType.typeName);
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