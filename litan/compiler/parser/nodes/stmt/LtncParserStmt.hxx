#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses a variaty of statements
	class ParserStmt : public ParserNode<Stmt> {
	public:
		ParserStmt(
			const ParserNode<StmtBlock> & block,
			const ParserNode<Stmt> & ifelse,
			const ParserNode<Stmt> & assign,
			const ParserNode<Expr> & expr,
			const ParserNode<ExprCall> & call);
		
		virtual std::shared_ptr<Stmt> eval(ParserPackage & parsePkg) const override;
	private:

		std::shared_ptr<Stmt> stmt(ParserPackage & parsePkg) const; 
		std::shared_ptr<StmtFor> forLoop(ParserPackage & parsePkg) const;
		std::shared_ptr<StmtRepeat> repeatLoop(ParserPackage & parsePkg) const;
		std::shared_ptr<StmtWhile> whileLoop(ParserPackage & parsePkg) const;
		std::shared_ptr<StmtAsm> asmBlock(ParserPackage & parsePkg) const;
		
		const ParserNode<StmtBlock> & block; 
		const ParserNode<Stmt> & ifelse; 

		const ParserNode<Stmt> & assign; 
		const ParserNode<Expr> & expr; 
		const ParserNode<ExprCall> & call; 
	};
}