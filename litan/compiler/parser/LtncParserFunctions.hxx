#pragma once
#include "LtncAst.hxx"
#include "LtncParserPackage.hxx"
#include "LtncError.hxx"
#include "LtncErrorCreationParser.hxx"
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
		std::shared_ptr<Stmt> forLoop(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> repeatLoop(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> whileLoop(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> assembly(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> ifElse(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> codeBlock(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> assign(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> returnStmt(ParserPackage & parsePkg);
		std::shared_ptr<Stmt> justAnExpression(ParserPackage & parsePkg);


		// Expressions

		std::shared_ptr<Expr> expression(ParserPackage & parsePkg);
		std::shared_ptr<Expr> comparison(ParserPackage & parsePkg);
		std::shared_ptr<Expr> term(ParserPackage & parsePkg);
		std::shared_ptr<Expr> product(ParserPackage & parsePkg);
		std::shared_ptr<Expr> unary(ParserPackage & parsePkg);
		std::shared_ptr<Expr> primary(ParserPackage & parsePkg);
		std::shared_ptr<ExprVar> var(ParserPackage & parsePkg);
		std::shared_ptr<ExprCall> call(ParserPackage & parsePkg);

		// literals
		std::shared_ptr<Expr> intLiteral(ParserPackage & parsePkg);
		std::shared_ptr<Expr> floatLiteral(ParserPackage & parsePkg);
		std::shared_ptr<Expr> stringLiteral(ParserPackage & parsePkg);
		std::shared_ptr<Expr> nulLiteral(ParserPackage & parsePkg);

		// Utility
		Namespace nameSpace(ParserPackage & parsePkg); 
		TypeId typeId(ParserPackage & parsePkg);
		Symbol functionSymbol(ParserPackage & parsePkg);
	}
}