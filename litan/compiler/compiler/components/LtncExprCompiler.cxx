#include "LtncExprCompiler.hxx"

#include "LtncAddEvaluator.hxx"
#include "LtncSubEvaluator.hxx"
#include "LtncMltEvaluator.hxx"
#include "LtncDivEvaluator.hxx"
#include "LtncModEvaluator.hxx"

#include "Unused.hxx"
#include <iostream>
#include <sstream>
#include <functional>

ltnc::ExprInfo ltnc::ExprCompiler::compile(CompilerPack & compPkg, const std::shared_ptr<Expr> & expr) const {
	return this->compileExpr(compPkg, expr);
}


ltnc::ExprInfo ltnc::ExprCompiler::compileExpr(CompilerPack & compPkg,  std::shared_ptr<Expr> expr) const {
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprIntLiteral>(expr)) {
		return this->compileIntLit(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprFltLiteral>(expr)) {
		return this->compileFltLit(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprStrLiteral>(expr)) {
		return this->compileStrLit(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprVar>(expr)) {
		return this->compileVar(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprBinary>(expr)) {
		return this->compileBinary(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprCall>(expr)) {
		return this->compileCall(compPkg, expr_);
	}
	throw std::runtime_error("Invalid Expr");
}


ltnc::ExprInfo ltnc::ExprCompiler::compileBinary(CompilerPack & compPkg, std::shared_ptr<ExprBinary> expr) const {
	switch (expr->type)	{

	// comparision operator
	case TokenType::EQUAL:			return this->buildBinary(compPkg, expr, "eql");
	case TokenType::UNEQUAL: 		return this->buildBinary(compPkg, expr, "uneql");
	case TokenType::SMALLER: 		return this->buildBinary(compPkg, expr, "sml");
	case TokenType::SMALLEREQUAL: 	return this->buildBinary(compPkg, expr, "smleql");
	case TokenType::BIGGER: 		return this->buildBinary(compPkg, expr, "bgr");
	case TokenType::BIGGEREQUAL: 	return this->buildBinary(compPkg, expr, "bgreql");

	// arithmetic binary operators 
	case TokenType::PLUS: 			return this->buildBinary(compPkg, expr, "add", AddEvaluator());
	case TokenType::MINUS: 			return this->buildBinary(compPkg, expr, "sub", SubEvaluator());
	case TokenType::STAR: 			return this->buildBinary(compPkg, expr, "mlt", MltEvaluator());
	case TokenType::SLASH: 			return this->buildBinary(compPkg, expr, "div", DivEvaluator());
	case TokenType::MOD: 			return this->buildBinary(compPkg, expr, "mod", ModEvaluator());

	// error
	default: 						throw std::runtime_error("Invalid expression");
	}
}


ltnc::ExprInfo ltnc::ExprCompiler::buildBinary(
	CompilerPack & compPkg,
	std::shared_ptr<ExprBinary> expr,
	const std::string & command,
	const Evaluator & eval) const {
	

	// left and right
	ExprInfo l = this->compileExpr(compPkg, expr->l);
	ExprInfo r = this->compileExpr(compPkg, expr->r);

	// i or f for int or float
	std::string suffix = this->getSuffux(l, r);

	// try constant folding
	if(compPkg.getSettings().getOptimizationLevel()) {		
		if(auto optimized = eval.optimize(l, r)) {
			return *optimized;
		}
	}
	return ExprInfo(l.type, l.code + r.code + command + suffix + "\n");
}


ltnc::ExprInfo ltnc::ExprCompiler::buildBinary(
	CompilerPack & compPkg,
	std::shared_ptr<ExprBinary> expr,
	const std::string & command) const {
	// left and right expr
	ExprInfo l = this->compileExpr(compPkg, expr->l);
	ExprInfo r = this->compileExpr(compPkg, expr->r);

	// i or f for int or float
	std::string suffix = this->getSuffux(l, r);
	
	return ExprInfo(l.type, l.code + r.code + command + suffix + "\n");
}


ltnc::ExprInfo ltnc::ExprCompiler::compileIntLit(CompilerPack & compPkg, std::shared_ptr<ExprIntLiteral> expr) const {
	UNUSED(compPkg);
	std::int64_t value = expr->number;
	std::string code = "newi " + std::to_string(value) + "\n";
	return ExprInfo(Type("int"), code, Constant(value));
}


ltnc::ExprInfo ltnc::ExprCompiler::compileFltLit(CompilerPack & compPkg, std::shared_ptr<ExprFltLiteral> expr) const {
	UNUSED(compPkg);
	double value = expr->number;
	std::string code = "newf " + std::to_string(value) + "\n";
	return ExprInfo(Type("flt"), code, Constant(value));
}

ltnc::ExprInfo ltnc::ExprCompiler::compileStrLit(CompilerPack & compPkg, std::shared_ptr<ExprStrLiteral> expr) const {
	UNUSED(compPkg);
	std::string string = expr->string;
	std::vector<std::string> stringParts;
	for(unsigned idx = 0; idx < string.size(); idx+=6) {
		stringParts.push_back(string.substr(idx,6));
	}
	std::string code = "// " + expr->string + "\n";
	code += "string::new\n";
	for(const std::string & str : stringParts) {
		code += "string::data '" + str + "'\n";
	}
	return ExprInfo(Type("str"), code);
}

ltnc::ExprInfo ltnc::ExprCompiler::compileVar(CompilerPack & compPkg, std::shared_ptr<ExprVar> expr) const {
	// read access
	ExprInfo access = this->compileAccess(compPkg, expr);
	return access;
	// heap
}


ltnc::ExprInfo ltnc::ExprCompiler::compileAccess(CompilerPack & compPkg, const std::shared_ptr<ExprVar> & access, const std::optional<ExprInfo> & expr) const {
	std::stringstream code;
	Var var("", 0, "");


	// find next var
	std::function nextVar = [
		&path = access->path,
		&scopeStack = compPkg.getScopes(),
		&typeTable = compPkg.getTypeTable()
		] (
		unsigned i,
		const Var & lastVar)
		-> Var {
		
		// get address on stack
		if(i) {
			// lookup struct type
			const Type & type = typeTable.getType(lastVar.typeName);
			// search next member
			const auto & members = type.members; 
			for(const auto & newVar : members) {
				if(newVar->name == path[i]) {
					return *newVar;
				}
			}
			// undefined member
			throw std::runtime_error("struct " + lastVar.name + " does not contain variable: " + path[i]);
		}
		// stack
		else {
			return scopeStack.get().getVar(path[0]); 
		}
	};


	// generate code for acces
	std::function makeCode = [
		&path = access->path] (
		unsigned i,
		const Var & var,
		const std::optional<ExprInfo> & expr)
		-> std::string {
		std::stringstream code;

		// load from stack
		if(i == 0) {
			code << "load " << var.addr << "\n";
		}

		// write to heap
		else if(i == path.size() - 1 && expr) {
			code << "newl " << var.addr << "\n";
			code << expr->code;
			code << "array::set \n";
		}

		// load from heap
		else {
			code << "newl " << var.addr << "\n";
			code << "array::get \n";
		}

		return code.str();
	};


	// follow refs
	for(unsigned i = 0; i < access->path.size(); i++) {
		var = nextVar(i, var);
		code << makeCode(i, var, expr);
	}


	return ExprInfo(var.typeName, code.str());
}



std::string ltnc::ExprCompiler::getSuffux(const ExprInfo & l, const ExprInfo & r) const {
	// mismatch
	if(l.type != r.type) {
		throw std::runtime_error("Expression types do not match: \"" + l.code + "\" and \"" + r.code + "\"");
	}

	// integer
	if(l.type == "int") {
		return "i";
	}

	// float
	if(l.type == "flt") {
		return "f";
	}

	// if type is not int or flt
	throw std::runtime_error("Invalid Type for operation");
}


ltnc::ExprInfo ltnc::ExprCompiler::compileCall(CompilerPack & compPkg, std::shared_ptr<ExprCall> expr) const {
	std::string code;
	std::vector<Param> params;

	// parameter list
	for(const auto & expr : expr->paramExprs) {
		ExprInfo exprInfo = this->compileExpr(compPkg, expr);
		std::cout << exprInfo.type.name << std::endl;
		params.push_back(Param(exprInfo.type, ""));
		code += exprInfo.code;
	}

	if(auto fxInfo = compPkg.matchFunction(FxSignature(Type("voi"), expr->name, params))) {
		// create jump to fx
		code += "call "  + fxInfo->jumpMark + "\n";
		return ExprInfo(fxInfo->signature.returnType, code);
	}
	throw std::runtime_error("No matching function for: " + expr->name);
}
