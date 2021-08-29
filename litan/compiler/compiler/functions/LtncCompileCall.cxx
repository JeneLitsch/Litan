#include "LtncCompilerFunctions.hxx"

ltn::c::ExprInfo ltn::c::compile::call(CompilerPack & compPkg, const ExprCall & expr) {
	CodeBuffer code(compPkg.getSettings().areCommentsActive());
	std::vector<Param> params;

	// parameter list
	for(const auto & expr : expr.paramExprs) {
		ExprInfo exprInfo = expression(compPkg, *expr);
		params.push_back(Param(exprInfo.typeId, VarId("")));
		code << exprInfo.code;
	}
	ltn::c::Function function = [&expr, &params, &compPkg]() {
		FunctionSignature fxSig = FunctionSignature(TypeId(TVoid), expr.name, params, expr.ns);
		try {
	 		return compPkg.getSymbolTable().match(expr.debugInfo, fxSig, true);
		}
		catch(...) {
			try  {
	 			return compPkg.getSymbolTable().match(expr.debugInfo, fxSig, false);
			}
			catch(...) {
				throw error::noMatchingFunction(expr.debugInfo, fxSig);
			}
		}
	}();
	
	code << Inst::call(function.jumpMark);
	return ExprInfo(function.signature.returnType, code);
}
