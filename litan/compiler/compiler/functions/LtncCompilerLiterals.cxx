#include "LtncCompilerFunctions.hxx"

ltnc::ExprInfo ltnc::compile::intLiteral(CompilerPack & compPkg, const ExprIntLiteral & expr) {
	std::int64_t value = expr.number;
	CodeBuffer code = compPkg.codeBuffer();
	code << Inst::newi(value);
	return ExprInfo(TypeId(TInt), code, ConstValue(value));
}


ltnc::ExprInfo ltnc::compile::floatLiteral(CompilerPack & compPkg, const ExprFltLiteral & expr) {
	double value = expr.number;
	CodeBuffer code = compPkg.codeBuffer();
	code << Inst::newf(value);
	return ExprInfo(TypeId(TFloat), code, ConstValue(value));
}


ltnc::ExprInfo ltnc::compile::stringLiteral(CompilerPack & compPkg, const ExprStrLiteral & expr) {
	CodeBuffer code = compPkg.codeBuffer();
	code << Comment(expr.string);
	code << AssemblyCode("heap::allocate::string");
	code << Inst::stringData(expr.string);
	return ExprInfo(TypeId(TString), code);
}

ltnc::ExprInfo ltnc::compile::nul() {
	CodeBuffer code(false);
	code << Inst::newl(0);
	return ExprInfo(TypeId(TPointer), code);
}

ltnc::ExprInfo ltnc::compile::boolLiteral(const ExprBool & expr) {
	CodeBuffer code(false);
	code << Inst::newl(expr.value);
	return ExprInfo(TypeId(TBool), code);
}
