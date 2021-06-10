#pragma once 
#include "LtncParserNode.hxx"
#
namespace ltnc {
	// Parses an assignmet operation
	class ParserAssign : public ParserNode<Stmt> {
	public:
		void connect(const ParserNode<Expr> & expr);
		virtual std::shared_ptr<Stmt> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * expr; 
	};
}