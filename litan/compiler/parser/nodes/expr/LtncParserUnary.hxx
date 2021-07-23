#pragma once
#include "LtncExpr.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses primary expression 
	// literals, call and identifier
	class ParserUnary : public ParserNode<Expr> {
	public:
		ParserUnary(
			const ParserNode<Expr> & primary);

		virtual std::shared_ptr<Expr> eval(
			ParserPackage & parsePkg) const override;
	
	private:
		const ParserNode<Expr> * primary;
	};
}