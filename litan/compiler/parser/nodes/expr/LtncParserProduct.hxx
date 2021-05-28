#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserProduct : public ParserNode<Expr> {
	public:
		void connect(const ParserNode<Expr> & primary);
		virtual std::shared_ptr<Expr> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * primary; 
	};
}