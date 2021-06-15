#pragma once 
#include "LtncDecl.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserDeclVar : public ParserNode<DeclVar> {
	public:
		void connect(const ParserNode<Expr> & expr);
		virtual std::shared_ptr<DeclVar> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * expr;
	};
}