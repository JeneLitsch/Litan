#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses a function
	class ParserFunction : public ParserNode<DeclFunction> {
	public:
		ParserFunction(const ParserNode<StmtBlock> & block);
		
		virtual std::shared_ptr<DeclFunction> eval(ParserPackage & parsePkg) const override;
	private:
		std::string name(ParserPackage & parsePkg) const;
		std::vector<Param> parameterList(ParserPackage & parsePkg) const;
		TypeId returnType(ParserPackage & parsePkg) const;
		std::shared_ptr<StmtBlock> body(ParserPackage & parsePkg) const;

		bool isInline(ParserPackage & parsePkg) const;
		
		const ParserNode<StmtBlock> * block; 
	};
}