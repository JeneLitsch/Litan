#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses binary comparision operations 
	// == != < > >= <=
	class ParserComparison : public ParserNode<Expr> {
	public:
		ParserComparison(const ParserNode<Expr> & term);
		virtual std::shared_ptr<Expr> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * term; 
	};
}