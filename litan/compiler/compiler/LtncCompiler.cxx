#include "LtncCompiler.hxx"
#include <iostream>
#include "LtncBaseTypes.hxx"
#include "LtncCtorGenerator.hxx"
#include "LtncCompilerFunctions.hxx"
#include "LtnCumulatedError.hxx"

std::string ltnc::Compiler::compile(
	std::shared_ptr<Program> program,
	const CompilerSettings & settings){

	CtorGenerator ctorGenerator;
	CompilerPack compPkg(settings);
	ltn::CumulatedError cumulatedError;

	SymbolTable & sTable = compPkg.getSymbolTable();

	sTable.insert(Type(TVoid));
	sTable.insert(Type(TInt, {TBool, TRaw}));
	sTable.insert(Type(TBool, {TInt, TRaw}));
	sTable.insert(Type(TRaw));
	sTable.insert(Type(TFloat, {TRaw}));
	sTable.insert(Type(TPointer, {TRaw}));
	
	sTable.addFunctionScope(FunctionSignature(TypeId(TVoid), "", {}));

	CodeBuffer code = compPkg.codeBuffer();
	// register typedefs
	for(const Type & t : program->types) {
		Type type = t;
		if(t.id != TVoid) {
			type.castableTo.push_back(TypeId(TRaw));
			type.castableTo.push_back(TypeId(TPointer));
		}
		sTable.insert(type);
	}


	// register structs
	for(const DeclStruct & struct_ : program->structs) {
		try {
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
			sTable.insert(structType);
		}
		catch(const ltn::Error & error) {
			cumulatedError.pushError(error);
		}
	}


	// register functions
	for(const auto & function : program->functions) {
		try {
			sTable.insert(function->signature);
		}
		catch(const ltn::Error & error) {
			cumulatedError.pushError(error);
		}
	}
	
	// init code
	code << AssemblyCode("-> MAIN"); 
	code << compile::justAnExpression(compPkg, StmtExpr(DebugInfo(), std::make_shared<ExprCall>(DebugInfo(), "main", Namespace()))).code;
	code << AssemblyCode("exit");
	code << AssemblyCode("\n");

	// compile functions
	for(const auto & function : program->functions) {
		try {
			code << compile::function(compPkg, *function).code;
		}
		catch(const ltn::Error & error) {
			cumulatedError.pushError(error);
		}
	}
	if(cumulatedError.throwable()) {
		throw cumulatedError;
	}
	return code.str();
}