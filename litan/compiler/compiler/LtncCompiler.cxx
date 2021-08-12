#include "LtncCompiler.hxx"
#include <iostream>
#include "LtncBaseTypes.hxx"
#include "LtncCtorGenerator.hxx"
#include "LtncCompilerFunctions.hxx"
#include "LtnErrorReporter.hxx"

std::string ltnc::Compiler::compile(
	const Program & program,
	ltn::ErrorReporter & error,
	const CompilerSettings & settings){

	CtorGenerator ctorGenerator;
	CompilerPack compPkg(settings, error);

	SymbolTable & sTable = compPkg.getSymbolTable();

	DebugInfo misc(0,0, "", "");

	sTable.insert(misc, Type(TVoid));
	sTable.insert(misc, Type(TInt, {TBool, TRaw}));
	sTable.insert(misc, Type(TBool, {TInt, TRaw}));
	sTable.insert(misc, Type(TRaw));
	sTable.insert(misc, Type(TFloat, {TRaw}));
	sTable.insert(misc, Type(TPointer, {TRaw}));
	
	sTable.addFunctionScope(FunctionSignature(TypeId(TVoid), "", {}));

	CodeBuffer code = compPkg.codeBuffer();
	// register typedefs
	for(const auto & t : program.types) {
		Type type = *t;
		if(type.id != TVoid) {
			type.castableTo.push_back(TypeId(TRaw));
			type.castableTo.push_back(TypeId(TPointer));
		}
		sTable.insert(misc, type);
	}


	// register structs
	for(const auto & struct_ : program.structs) {
		try {
			Type structType(struct_->typeId);
			structType.castableTo.push_back(TypeId(TRaw));
			structType.castableTo.push_back(TypeId(TPointer));
			for(const auto & member : struct_->members) {
				if(member->assign) {
					throw std::runtime_error("Assignment to members is not allowed");
				}
				auto varId = member->varId;
				auto typeId = member->typeId;
				auto addr = structType.members.size();
				auto var = std::make_shared<Var>(typeId, addr, varId);
				structType.members.push_back(var);
			}
			// add automatic constructors
			code << ctorGenerator.defaultCtor(compPkg, structType);
			code << ctorGenerator.parameterCtor(compPkg, structType);
			sTable.insert(struct_->debugInfo, structType);
		}
		catch(const ltn::Error & error) {
			compPkg.error << error;
		}
	}


	// register functions
	for(const auto & function : program.functions) {
		try {
			sTable.insert(function->debugInfo, function->signature);
		}
		catch(const ltn::Error & error) {
			compPkg.error << error;
		}
	}
	
	try {
		// init code
		code << AssemblyCode("-> MAIN"); 
		code << compile::justAnExpression(compPkg, StmtExpr(DebugInfo(), std::make_unique<ExprCall>(DebugInfo(), "main", Namespace()))).code;
		code << AssemblyCode("exit");
		code << AssemblyCode("\n");
	}
	catch(const ltn::Error & error) {
		compPkg.error << error;
	}

	// compile functions
	for(const auto & function : program.functions) {
		try {
			code << compile::function(compPkg, *function).code;
		}
		catch(const ltn::Error & error) {
			compPkg.error << error;
		}
	}

	return code.str();
}