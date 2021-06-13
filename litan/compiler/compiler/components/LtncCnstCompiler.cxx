#include "LtncCnstCompiler.hxx"


ltnc::CnstCompiler::CnstCompiler() {}

ltnc::ExprInfo ltnc::CnstCompiler::compile(
	CompilerPack & compPkg,
	const std::shared_ptr<ExprNew> & exprNew) const {
	return this->defaultConstructor(compPkg, exprNew);
}

ltnc::ExprInfo ltnc::CnstCompiler::defaultConstructor(
	CompilerPack & compPkg,
	const std::shared_ptr<ExprNew> & exprNew) const {
	const std::string typeName = exprNew->typeName;
	const Type & type = compPkg.getTypeTable().getType(typeName);

	
	CodeBuffer code = compPkg.codeBuffer();
	code << Comment(exprNew->typeName);
	code << AssemblyCode("array::new");
	for(const auto & member : type.members) {
		code << AssemblyCode("copy");
		code << Inst::newl(0); // init with nullptr;
		code << AssemblyCode("array::add");
	}
	return ExprInfo(exprNew->typeName, code);
}	