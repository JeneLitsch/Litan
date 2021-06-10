#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses addition and subtraction
	class ParserTerm : public ParserNode<Expr> {
	public:
		void connect(const ParserNode<Expr> & product);
		virtual std::shared_ptr<Expr> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * product; 
	};
}