#include "LtncCompiler.hxx"

std::string ltnc::Compiler::compile(
	std::shared_ptr<Program> program,
	const CompilerSettings & settings){
	CompilerPack compPkg(settings);

	compPkg.getTypeTable().registerType("voi");
	compPkg.getTypeTable().registerType("int");
	compPkg.getTypeTable().registerType("flt");
	compPkg.getTypeTable().registerType("arr");
	compPkg.getTypeTable().registerType("str");

	for(const Type & type : program->types) {
		compPkg.getTypeTable().registerType(type.typeName);
	}

	compPkg.getScopes().addFunctionScope(FxSignature(Type("voi"), "", {}));
	for(const auto & function : program->functions) {
		compPkg.registerFunction(function);
	}
	std::string code;
	code += "-> MAIN \n"; 
	code += stmtCompiler.compileEval(compPkg, std::make_shared<StmtExpr>(std::make_shared<ExprCall>("main"))).code;
	code += "exit \n";
	code += "\n\n";
	for(const auto & function : program->functions) {
		code += this->declCompiler.compile(compPkg, function).code;
	}
	return code;
}
