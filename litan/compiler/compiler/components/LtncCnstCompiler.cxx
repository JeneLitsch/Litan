#include "LtncCnstCompiler.hxx"
#include "LtncExprCompiler.hxx"
#include "Unused.hxx"

ltnc::CnstCompiler::CnstCompiler(const ExprCompiler & exprCompiler) : exprCompiler(exprCompiler) {}

ltnc::ExprInfo ltnc::CnstCompiler::compile(
	CompilerPack & compPkg,
	const std::shared_ptr<ExprNew> & exprNew) const {
	if(exprNew->paramExprs.empty()) {
		return this->defaultConstructor(compPkg, exprNew);
	}
	return this->parameterConstructor(compPkg, exprNew);
}

ltnc::ExprInfo ltnc::CnstCompiler::defaultConstructor(
	CompilerPack & compPkg,
	const std::shared_ptr<ExprNew> & exprNew) const {
	const Type & type = compPkg.getSymbolTable().match(exprNew->typeId);

	
	CodeBuffer code = compPkg.codeBuffer();
	code << Comment(exprNew->typeId.name);
	code << AssemblyCode("array::new");
	for(const auto & member : type.members) {
		UNUSED(member);
		code << AssemblyCode("copy");
		code << Inst::newl(0); // init with nullptr;
		code << AssemblyCode("array::pushb");
	}
	return ExprInfo(TypeId(exprNew->typeId), code);
}	


ltnc::ExprInfo ltnc::CnstCompiler::parameterConstructor(
	CompilerPack & compPkg,
	const std::shared_ptr<ExprNew> & exprNew) const {
	const Type & type = compPkg.getSymbolTable().match(exprNew->typeId);

	unsigned provided = exprNew->paramExprs.size();
	unsigned expected = type.members.size();

	if(provided != expected) {
		throw std::runtime_error(
			std::to_string(expected) + " parameters expected " +
			std::to_string(provided) + " provided");
	}

	unsigned exprCount = provided;

	CodeBuffer code = compPkg.codeBuffer();
	code << Comment(exprNew->typeId.name);
	code << AssemblyCode("array::new");
	for(unsigned i = 0; i < exprCount; i++) {
		const auto & member = type.members[i];
		const auto & param = exprNew->paramExprs[i];
		ExprInfo expr = this->exprCompiler.compile(compPkg, param);
		if(member->typeId != expr.typeId) {
			throw std::runtime_error(
				"Types do not match: Expected " + member->typeId.name
				+ " instead of " + expr.typeId.name);
		}

		code << AssemblyCode("copy");
		code << expr.code;
		code << AssemblyCode("array::pushb");
	}
	return ExprInfo(TypeId(exprNew->typeId), code);
}	