#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LtncAstNode.hxx"
#include "LtncType.hxx"
#include "LtncVar.hxx"
#include "LtncFunctionSignature.hxx"
#include "LtncStmt.hxx"
namespace ltnc {
	struct Stmt;
	struct StmtVar;
	
	struct Decl : public AstNode {
		Decl(const DebugInfo & debugInfo) : AstNode(debugInfo) {}	
		virtual ~Decl() = default;
	};




	struct DeclFunction : public Decl {
		DeclFunction(
			const DebugInfo & debugInfo,
			const FunctionSignature & signature,
			std::shared_ptr<Stmt> body) 
		:	Decl(debugInfo),
			signature(signature),
			body(body) {}

		virtual ~DeclFunction() = default;
		FunctionSignature signature;
		std::shared_ptr<Stmt> body;
	};

	struct DeclStruct : public Decl {
		DeclStruct(
			const DebugInfo & debugInfo,
			const TypeId & typeId,
			const std::vector<StmtVar> & members)
		:	Decl(debugInfo),
			typeId(typeId),
			members(members) {}
		
		TypeId typeId;
		std::vector<StmtVar> members;
	};
}