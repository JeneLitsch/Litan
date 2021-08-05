#include "LtncCompilerFunctions.hxx"
#include <functional>

ltnc::ExprInfo ltnc::compile::var(CompilerPack & compPkg, const ExprVar & varExpr, const std::optional<ExprInfo> & expr) {

	CodeBuffer code = compPkg.codeBuffer();
	Var var(TypeId(""), 0, VarId(""));


	// find next var
	std::function nextVar = [
		&path = varExpr.path,
		&scopeStack = compPkg.getSymbolTable(),
		&typeTable = compPkg.getSymbolTable(),
		&varExpr
		] (
		unsigned i,
		const Var & lastVar)
		-> Var {
		
		// get address on stack
		if(i) {
			// lookup struct type
			const Type & type = typeTable.match(lastVar.typeId);
			// search next member
			const auto & members = type.members; 
			for(const auto & newVar : members) {
				if(newVar->name == path[i]) {
					return *newVar;
				}
			}
			// undefined member
			throw error::notAMember(path[i], type.id, varExpr.debugInfo);
		}
		// stack
		else {
			try {
				return scopeStack.match(VarId(path[0])); 
			}
			catch(...) {
				throw error::undefinedVariable(path[i], varExpr.debugInfo);
			}
		}
	};


	// generate code for acces
	std::function makeCode = [
		&path = varExpr.path] (
		unsigned i,
		const Var & var,
		const std::optional<ExprInfo> & expr)
		-> CodeBuffer {
		CodeBuffer code(false);

		// stack
		if(i == 0) {
			if(path.size() == 1 && expr) {
				code << expr->code;
				code << Inst::store(var.addr);
			}
			else {
				code << Inst::load(var.addr);
			}
		}

		// heap
		else {
			if(i == path.size() - 1 && expr) {
				code << Inst::newl(var.addr);
				code << expr->code;
				code << AssemblyCode("array::set");
			}
			else {
				code << Inst::newl(var.addr);
				code << AssemblyCode("array::get");
			}
		}

		return code;
	};


	// follow refs
	for(unsigned i = 0; i < varExpr.path.size(); i++) {
		var = nextVar(i, var);
		code << makeCode(i, var, expr);
	}


	return ExprInfo(var.typeId, code);
}


