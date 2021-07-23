#pragma once 
#include "LtncDecl.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserDeclVar : public ParserNode<DeclVar> {
	public:
		ParserDeclVar(const ParserNode<Expr> & expr);
		virtual std::shared_ptr<DeclVar> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * expr;
	};
}