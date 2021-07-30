#include "LtncCompilerFunctions.hxx"

ltnc::ExprInfo ltnc::compile::call(CompilerPack & compPkg, const ExprCall & expr) {
	CodeBuffer code(compPkg.getSettings().areCommentsActive());
	std::vector<Param> params;

	// parameter list
	for(const auto & expr : expr.paramExprs) {
		ExprInfo exprInfo = expression(compPkg, *expr);
		params.push_back(Param(exprInfo.typeId, VarId("")));
		code << exprInfo.code;
	}
	ltnc::Function fxInfo = [&expr, &params, &compPkg]() {
		FunctionSignature fxSig = FunctionSignature(TypeId(TVoid), expr.name, params, expr.ns);
		try {
	 		return compPkg.getSymbolTable().match(fxSig, true);
		}
		catch(...) {
	 		return compPkg.getSymbolTable().match(fxSig, false);
		}
	}();
	
	code << AssemblyCode("call "  + fxInfo.jumpMark);
	return ExprInfo(fxInfo.signature.returnType, code);
}
