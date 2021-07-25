#pragma once 
#include "LtncParserNode.hxx"
namespace ltnc {
	// ParserNode for return statement
	class ParserReturn : public ParserNode<StmtBlock> {
	public:
		ParserReturn(const ParserNode<Expr> & expr);		
		virtual std::shared_ptr<StmtBlock> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> & expr; 
	};
}