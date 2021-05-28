#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserComparison : public ParserNode<Expr> {
	public:
		void connect(const ParserNode<Expr> & term);
		virtual std::shared_ptr<Expr> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * term; 
	};
}