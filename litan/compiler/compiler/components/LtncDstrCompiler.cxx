#include "LtncDstrCompiler.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncVariCompiler.hxx"

ltnc::DstrCompiler::DstrCompiler(
	const VariCompiler & variCompiler)
	:
	variCompiler(variCompiler) 
	{}

ltnc::ExprInfo ltnc::DstrCompiler::compile(
	CompilerPack & compPkg,
	const std::shared_ptr<ExprDel> & exprDel) const {

	ExprInfo exprInfo = this->variCompiler.compile(compPkg, exprDel->exprVar, {});

	const Type & type = compPkg.getSymbolTable().getType(exprInfo.type.name);
	
	ExprInfo setNull = this->variCompiler.compile(compPkg, exprDel->exprVar, this->nullPtr(type));

	if(type.members.empty()) {
		throw std::runtime_error("Type " + type.name + " is not a heap allocated struct");
	}
	CodeBuffer code = compPkg.codeBuffer();
	code << exprInfo.code;
	code << AssemblyCode("heap::del");
	code << setNull.code;
	return ExprInfo(Type("voi"), code);
}

ltnc::ExprInfo ltnc::DstrCompiler::nullPtr(const Type & type) const {
	CodeBuffer code(false);
	code << AssemblyCode("newl 0");
	ExprInfo nullPtr = ExprInfo(type, code);
	return nullPtr;
}