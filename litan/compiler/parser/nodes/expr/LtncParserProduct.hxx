#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses multiplication and division
	class ParserProduct : public ParserNode<Expr> {
	public:
		ParserProduct(const ParserNode<Expr> & unary);
		virtual std::shared_ptr<Expr> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * unary; 
	};
}