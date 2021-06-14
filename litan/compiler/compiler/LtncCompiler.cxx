#include "LtncCompiler.hxx"
#include <iostream>
std::string ltnc::Compiler::compile(
	std::shared_ptr<Program> program,
	const CompilerSettings & settings){
	CompilerPack compPkg(settings);
	CodeBuffer code = compPkg.codeBuffer();

	// register types
	for(const Type & type : program->types) {
		compPkg.getSymbolTable().insert(type);
	}

	for(const DeclStruct & struct_ : program->structs) {
		Type structType(struct_.name);
		for(const auto & member : struct_.members) {
			auto name = member->name;
			auto type = member->type;
			auto addr = structType.members.size();
			auto var = std::make_shared<Var>(type.name, addr, name);
			structType.members.push_back(var);
		}
		compPkg.getSymbolTable().insert(structType);
	}

	// register functions
	for(const auto & function : program->functions) {
		compPkg.getSymbolTable().insert(function->signature);
	}
	
	// init code
	compPkg.getSymbolTable().addFunctionScope(FxSignature(Type("voi"), "", {}));
	code << AssemblyCode("-> MAIN"); 
	code << stmtCompiler.compileEval(compPkg, std::make_shared<StmtExpr>(std::make_shared<ExprCall>("main"))).code;
	code << AssemblyCode("exit");
	code << AssemblyCode("\n");

	// compile functions
	for(const auto & function : program->functions) {
		code << this->declCompiler.compile(compPkg, function).code;
	}

	return code.str();
}
