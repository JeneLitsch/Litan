#pragma once 
#include "LtncParserNode.hxx"
#include "LtncDecl.hxx"
namespace ltnc {
	class ParserBlock : public ParserNode<StmtBlock> {
	public:
		void connect(
			const ParserNode<Stmt> & stmt,
			const ParserNode<DeclVar> & declVar);
		
		virtual std::shared_ptr<StmtBlock> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<DeclVar> * declVar; 
		const ParserNode<Stmt> * stmt; 
	};
}