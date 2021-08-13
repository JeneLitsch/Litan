#include "LtncCompilerFunctions.hxx"

std::string fxComment(const ltn::c::DeclFunction & decl) {
	std::string text;
	text += decl.signature.name + " ( ";
	for (const auto & param : decl.signature.params) {
		text += param.typeId.name + " ";
	}
	text += "-> ";
	text += decl.signature.returnType.name + " ) ";
	return text;
}

ltn::c::StmtInfo ltn::c::compile::function(
	CompilerPack & compPkg,
	const DeclFunction & decl) {
		
	const Function & func = compPkg.getSymbolTable().match(decl.debugInfo, decl.signature);
	compPkg.getSymbolTable().match(decl.debugInfo, decl.signature.returnType);
	compPkg.getSymbolTable().addFunctionScope(func.signature);
	
	// register parameter
	for(const Param & param : decl.signature.params) {
		compPkg.getSymbolTable().match(decl.debugInfo, param.typeId);
		compPkg.getSymbolTable().insert(decl.debugInfo, param.name, TypeId(param.typeId));
		if(param.typeId == TVoid) {
			throw error::voidParameter(decl.debugInfo);
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
		std::uint64_t varAddr = compPkg.getSymbolTable().match(decl.debugInfo, VarId((*param).name)).addr;
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


