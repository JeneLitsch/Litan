#include "LtncCompilerFunctions.hxx"

std::string fxComment(const ltnc::DeclFunction & decl) {
	std::string text;
	text += decl.signature.name + " ( ";
	for (const auto & param : decl.signature.params) {
		text += param.typeId.name + " ";
	}
	text += "-> ";
	text += decl.signature.returnType.name + " ) ";
	return text;
}

ltnc::StmtInfo ltnc::compile::function(
	CompilerPack & compPkg,
	const DeclFunction & decl) {
		
	const Func & func = compPkg.getSymbolTable().match(decl.signature);
	compPkg.getSymbolTable().match(decl.signature.returnType);
	compPkg.getSymbolTable().addFunctionScope(func.signature);
	
	// register parameter
	for(const Param & param : decl.signature.params) {
		compPkg.getSymbolTable().match(param.typeId);
		compPkg.getSymbolTable().insert(param.name, TypeId(param.typeId));
		if(param.typeId == TVoid) {
			throw std::runtime_error("Void is not an allowed paramter type");
		}
	}
	// eval body
	StmtInfo body = statement(compPkg, *decl.body);

	// create code;
	CodeBuffer code = compPkg.codeBuffer();
	code << Comment(fxComment(decl));
	code << AssemblyCode("-> " + func.jumpMark);
	// load params into memory (backwards because LIFO)
	const auto & params = decl.signature.params; 
	code << AssemblyCode("stackalloc " + std::to_string(body.stackalloc + params.size()));
	for(auto param = params.rbegin(); param != params.rend(); ++param) {
		// store parameter;
		std::uint64_t varAddr = compPkg.getSymbolTable().match(VarId((*param).name)).addr;
		code << Inst::store(static_cast<std::uint32_t>(varAddr));
	}
	code << body.code;
	if(decl.signature.returnType == TVoid) {
		code << AssemblyCode("return");
	}
	else {
		code << AssemblyCode("error");
	}
	code << AssemblyCode("\n");
	compPkg.getSymbolTable().remove();
	return StmtInfo(code, 0);
}


