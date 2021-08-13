#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LtncAstNode.hxx"
#include "LtncType.hxx"
#include "LtncVar.hxx"
#include "LtncFunctionSignature.hxx"
#include "LtncStmt.hxx"
namespace ltn::c {
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
			std::unique_ptr<Stmt> body) 
		:	Decl(debugInfo),
			signature(signature),
			body(std::move(body)) {}

		virtual ~DeclFunction() = default;
		FunctionSignature signature;
		std::unique_ptr<Stmt> body;
	};

	struct DeclStruct : public Decl {
		DeclStruct(
			const DebugInfo & debugInfo,
			const TypeId & typeId,
			std::vector<std::unique_ptr<StmtVar>> members)
		:	Decl(debugInfo),
			typeId(typeId),
			members(std::move(members)) {}
		
		TypeId typeId;
		std::vector<std::unique_ptr<StmtVar>> members;
	};
}