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
	std::string string = expr.string;
	std::vector<std::string> stringParts;
	for(unsigned idx = 0; idx < string.size(); idx+=6) {
		stringParts.push_back(string.substr(idx,6));
	}
	CodeBuffer code = compPkg.codeBuffer();
	code << Comment(expr.string);
	code << AssemblyCode("heap::allocate::string");
	for(const std::string & str : stringParts) {
		code << AssemblyCode("string::data '" + str + "'");
	}
	return ExprInfo(TypeId(TString), code);
}