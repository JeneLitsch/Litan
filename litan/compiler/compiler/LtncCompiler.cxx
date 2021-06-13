#include "LtncCompiler.hxx"
#include <iostream>
std::string ltnc::Compiler::compile(
	std::shared_ptr<Program> program,
	const CompilerSettings & settings){
	CompilerPack compPkg(settings);
	std::string code;

	// register types
	for(const Type & type : program->types) {
		compPkg.getTypeTable().registerType(type);
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
		compPkg.getTypeTable().registerType(structType);
	}

	// register functions
	for(const auto & function : program->functions) {
		compPkg.registerFunction(function);
	}
	
	// init code
	compPkg.getScopes().addFunctionScope(FxSignature(Type("voi"), "", {}));
	code += "-> MAIN \n"; 
	code += stmtCompiler.compileEval(compPkg, std::make_shared<StmtExpr>(std::make_shared<ExprCall>("main"))).code;
	code += "exit \n";
	code += "\n\n";

	if (settings.getOptimizationLevel()) {
		// compile functions
		for(auto & fx : program->functions) {
			if(fx->inlined) {
				std::string fxCode = this->declCompiler.compile(compPkg, fx).code;
				compPkg.addInlineCode(fx->signature, code);
			}
		}
	}

	// compile functions
	for(const auto & function : program->functions) {
		code += this->declCompiler.compile(compPkg, function).code;
	}

	return code;
}
