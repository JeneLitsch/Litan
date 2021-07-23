#include "LtncCompiler.hxx"
#include <iostream>
#include "LtncBaseTypes.hxx"
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
		Type structType(struct_.typeId);
		for(const auto & member : struct_.members) {
			if(member->assign) {
				throw std::runtime_error("Assignment to members is not allowed");
			}
			auto name = member->name;
			auto typeId = member->typeId;
			auto addr = structType.members.size();
			auto var = std::make_shared<Var>(typeId, addr, name);
			structType.members.push_back(var);
		}
		compPkg.getSymbolTable().insert(structType);
	}


	// for(const auto & uniform : program->uniforms) {
	// 	code << Comment("uniform : " + uniform->typeId.name + " " + uniform->constId.name);
	// 	ConstValue value = this->findUniformValue(
	// 		uniform->constId,
	// 		uniform->typeId,
	// 		uniforms);
	// 	compPkg.getSymbolTable().insert(uniform->constId, uniform->typeId, value);
	// }

	// register functions
	for(const auto & function : program->functions) {
		compPkg.getSymbolTable().insert(function->signature);
	}
	
	// init code
	compPkg.getSymbolTable().addFunctionScope(FunctionSignature(TypeId(TVoid), "", {}));
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

// ltnc::ConstValue ltnc::Compiler::findUniformValue(
// 	const ConstantId & constId,
// 	const TypeId & typeId,
// 	const std::map<ConstantId, ConstValue> & uniforms) const { 
// 	if (typeId != TypeId("int") && typeId != TypeId("flt")) {
// 		throw std::runtime_error("Only int and flt are supported for uniforms");
// 	}
// 	for(const auto & uniform : uniforms) {
// 		if(uniform.first.name == constId.name) {
// 			return uniform.second;
// 		}
// 	}
// 	throw std::runtime_error("Not matching uniform value for " + constId.name);
// }