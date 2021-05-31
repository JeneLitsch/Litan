#pragma once 
#include "LtncParserNode.hxx"
#include "LtncDecl.hxx"
namespace ltnc {
	class ParserBlock : public ParserNode<StmtBlock> {
	public:
		void connect(
			const ParserNode<Stmt> & stmt,
			const ParserNode<DeclVar> & declInt,
			const ParserNode<DeclVar> & declFlt,
			const ParserNode<DeclVar> & declArr,
			const ParserNode<DeclVar> & declStr);
		
		virtual std::shared_ptr<StmtBlock> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<DeclVar> * declInt; 
		const ParserNode<DeclVar> * declFlt; 
		const ParserNode<DeclVar> * declArr; 
		const ParserNode<DeclVar> * declStr; 
		const ParserNode<Stmt> * stmt; 
	};
}