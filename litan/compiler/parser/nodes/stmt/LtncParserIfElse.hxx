#pragma once 
#include "LtncParserNode.hxx"
namespace ltnc {
	// Parses if statement with optional else
	class ParserIfElse : public ParserNode<Stmt> {
	public:
		ParserIfElse(const ParserNode<Stmt> & stmt, const ParserNode<Expr> & expr);
		virtual std::shared_ptr<Stmt> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Stmt> * stmt; 
		const ParserNode<Expr> * expr; 
	};
}