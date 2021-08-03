#include "LtncCompiler.hxx"
#include <iostream>
#include "LtncBaseTypes.hxx"
#include "LtncCtorGenerator.hxx"
#include "LtncCompilerFunctions.hxx"

std::string ltnc::Compiler::compile(
	std::shared_ptr<Program> program,
	const CompilerSettings & settings){

	CtorGenerator ctorGenerator;

	CompilerPack compPkg(settings);
	compPkg.getSymbolTable().addFunctionScope(FunctionSignature(TypeId(TVoid), "", {}));
	CodeBuffer code = compPkg.codeBuffer();
	// register typedefs
	for(const Type & t : program->types) {
		Type type = t;
		if(t.id != TVoid) {
			type.castableTo.push_back(TypeId(TRaw));
			type.castableTo.push_back(TypeId(TPointer));
		}
		compPkg.getSymbolTable().insert(type);
	}


	// register structs
	for(const DeclStruct & struct_ : program->structs) {
		Type structType(struct_.typeId);
		structType.castableTo.push_back(TypeId(TRaw));
		structType.castableTo.push_back(TypeId(TPointer));
		for(const auto & member : struct_.members) {
			if(member.assign) {
				throw std::runtime_error("Assignment to members is not allowed");
			}
			auto varId = member.varId;
			auto typeId = member.typeId;
			auto addr = structType.members.size();
			auto var = std::make_shared<Var>(typeId, addr, varId);
			structType.members.push_back(var);
		}
		// add automatic constructors
		code << ctorGenerator.defaultCtor(compPkg, structType);
		code << ctorGenerator.parameterCtor(compPkg, structType);
		compPkg.getSymbolTable().insert(structType);
	}


	// register functions
	for(const auto & function : program->functions) {
		compPkg.getSymbolTable().insert(function->signature);
	}
	
	// init code
	code << AssemblyCode("-> MAIN"); 
	code << compile::justAnExpression(compPkg, StmtExpr(std::make_shared<ExprCall>("main", Namespace()))).code;
	code << AssemblyCode("exit");
	code << AssemblyCode("\n");

	// compile functions
	for(const auto & function : program->functions) {
		code << compile::function(compPkg, *function).code;
	}

	return code.str();
}