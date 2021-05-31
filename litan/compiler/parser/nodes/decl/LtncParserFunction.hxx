#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserFunction : public ParserNode<DeclFunction> {
	public:
		void connect(const ParserNode<StmtBlock> & block);
		
		virtual std::shared_ptr<DeclFunction> eval(ParserPackage & parsePkg) const override;
	private:

		std::shared_ptr<DeclFunction> function(ParserPackage & parsePkg) const;
		Type toType(TokenType tokenType) const;
		const ParserNode<StmtBlock> * block; 
	};
}