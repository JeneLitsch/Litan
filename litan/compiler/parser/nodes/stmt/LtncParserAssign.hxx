#pragma once 
#include "LtncParserNode.hxx"
#
namespace ltnc {
	// Parses an assignmet operation
	class ParserAssign : public ParserNode<Stmt> {
	public:
		ParserAssign(const ParserNode<Expr> & expr, const ParserNode<ExprVar> & var);
		virtual std::shared_ptr<Stmt> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<Expr> * expr; 
		const ParserNode<ExprVar> * var; 
	};
}