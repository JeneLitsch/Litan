#pragma once
#include "LtncAst.hxx"
#include "LtncParserPackage.hxx"
#include "LtncError.hxx"
#include "LtncErrorCreationParser.hxx"
namespace ltnc {
	namespace parse {
		
		// Declarations
		std::unique_ptr<DeclStruct> declareStruct(ParserPackage & parsePkg);
		std::unique_ptr<Type> declareType(ParserPackage & parsePkg);
		std::unique_ptr<DeclFunction> declareFunction(ParserPackage & parsePkg);
		void declaration(ParserPackage & parsePkg, Program & program);
		// Statement

		std::unique_ptr<StmtVar> declareVar(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> statement(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> forLoop(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> repeatLoop(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> whileLoop(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> assembly(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> ifElse(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> codeBlock(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> assign(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> returnStmt(ParserPackage & parsePkg);
		std::unique_ptr<Stmt> justAnExpression(ParserPackage & parsePkg);


		// Expressions

		std::unique_ptr<Expr> expression(ParserPackage & parsePkg);
		std::unique_ptr<Expr> logicAnd(ParserPackage & parsePkg);
		std::unique_ptr<Expr> logicOr(ParserPackage & parsePkg);
		std::unique_ptr<Expr> equality(ParserPackage & parsePkg);
		std::unique_ptr<Expr> comparison(ParserPackage & parsePkg);
		std::unique_ptr<Expr> threeWay(ParserPackage & parsePkg);
		std::unique_ptr<Expr> term(ParserPackage & parsePkg);
		std::unique_ptr<Expr> product(ParserPackage & parsePkg);
		std::unique_ptr<Expr> exponent(ParserPackage & parsePkg);
		std::unique_ptr<Expr> unary(ParserPackage & parsePkg);
		std::unique_ptr<Expr> primary(ParserPackage & parsePkg);
		std::unique_ptr<ExprVar> var(ParserPackage & parsePkg);
		std::unique_ptr<ExprCall> call(ParserPackage & parsePkg);

		// literals
		std::unique_ptr<Expr> literal(ParserPackage & parsePkg);
		std::unique_ptr<Expr> intLiteral(ParserPackage & parsePkg);
		std::unique_ptr<Expr> floatLiteral(ParserPackage & parsePkg);
		std::unique_ptr<Expr> stringLiteral(ParserPackage & parsePkg);
		std::unique_ptr<Expr> nulLiteral(ParserPackage & parsePkg);
		std::unique_ptr<Expr> boolLiteral(ParserPackage & parsePkg);

		// Utility
		Namespace nameSpace(ParserPackage & parsePkg); 
		TypeId typeId(ParserPackage & parsePkg);
		Symbol functionSymbol(ParserPackage & parsePkg);
	}
}