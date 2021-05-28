#pragma once 
#include "LtncParserNode.hxx"
namespace ltnc {
	class ParserIfElse : public ParserNode<Stmt> {
	public:
		void connect(const ParserNode<Stmt> & stmt, const ParserNode<Expr> & expr);
		virtual std::shared_ptr<Stmt> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Stmt> * stmt; 
		const ParserNode<Expr> * expr; 
	};
}