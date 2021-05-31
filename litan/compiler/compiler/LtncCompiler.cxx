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

	return stmtCompiler.compileProgram(compPkg, program);
}
