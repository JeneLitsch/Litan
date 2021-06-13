#include "LtncDstrCompiler.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncVariCompiler.hxx"

ltnc::DstrCompiler::DstrCompiler(
	const ExprCompiler & exprCompiler,
	const VariCompiler & variCompiler)
	:
	exprCompiler(exprCompiler),
	variCompiler(variCompiler) 
	{}

ltnc::ExprInfo ltnc::DstrCompiler::compile(
	CompilerPack & compPkg,
	const std::shared_ptr<ExprDel> & exprDel) const {


	ExprInfo exprInfo = this->variCompiler.compile(compPkg, exprDel->exprVar, {});
	const Type & type = compPkg.getTypeTable().getType(exprInfo.type.name);
	if(type.members.empty()) {
		throw std::runtime_error("Type " + type.name + " is not a heap allocated struct");
	}
	CodeBuffer code = compPkg.codeBuffer();
	code << exprInfo.code;
	code << AssemblyCode("heap::del");
	return ExprInfo(Type("voi"), code);
}