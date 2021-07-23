#pragma once 
#include "LtncParserNode.hxx"
#include "LtncDecl.hxx"
namespace ltnc {
	// Parses code block until "}"
	class ParserBlock : public ParserNode<StmtBlock> {
	public:
		ParserBlock(
			const ParserNode<Stmt> & stmt,
			const ParserNode<DeclVar> & declVar);
		
		virtual std::shared_ptr<StmtBlock> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<DeclVar> * declVar; 
		const ParserNode<Stmt> * stmt; 
	};
}