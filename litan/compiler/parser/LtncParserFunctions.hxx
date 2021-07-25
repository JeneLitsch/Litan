#pragma once
#include "LtncAst.hxx"
#include "LtncParserPackage.hxx"

namespace ltnc {
	namespace parse {
		
		// Declarations
		std::shared_ptr<DeclStruct> declareStruct(ParserPackage & parsePkg);
		std::shared_ptr<Type> declareType(ParserPackage & parsePkg);
		std::shared_ptr<DeclVar> declareVar(ParserPackage & parsePkg);
		std::shared_ptr<DeclFunction> declareFunction(ParserPackage & parsePkg);
		void declaration(ParserPackage & parsePkg, Program & program);

		// Statement

		std::shared_ptr<Stmt> statement(ParserPackage & parsePkg);
		std::shared_ptr<StmtFor> forLoop(ParserPackage & parsePkg);
		std::shared_ptr<StmtRepeat> repeatLoop(ParserPackage & parsePkg);
		std::shared_ptr<StmtWhile> whileLoop(ParserPackage & parsePkg);
		std::shared_ptr<StmtAsm> assembly(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> ifElse(ParserPackage & parsePkg);
		std::shared_ptr<StmtBlock> codeBlock(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> assign(ParserPackage & parsePkg);


		// Expressions

		std::shared_ptr<Expr> expression(ParserPackage & parsePkg);
		std::shared_ptr<Expr> comparison(ParserPackage & parsePkg);
		std::shared_ptr<Expr> term(ParserPackage & parsePkg);
		std::shared_ptr<Expr> product(ParserPackage & parsePkg);
		std::shared_ptr<Expr> unary(ParserPackage & parsePkg);
		std::shared_ptr<Expr> primary(ParserPackage & parsePkg);
		std::shared_ptr<ExprVar> var(ParserPackage & parsePkg);
		std::shared_ptr<ExprCall> call(ParserPackage & parsePkg);
		std::shared_ptr<std::vector<std::shared_ptr<Expr>>> parameters(ParserPackage & parsePkg);


		// Utility
		Namespace nameSpace(ParserPackage & parsePkg); 
		TypeId type(ParserPackage & parsePkg);
	}
}