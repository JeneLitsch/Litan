#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LtncAstNode.hxx"
#include "LtncType.hxx"
#include "LtncVar.hxx"
#include "LtncFunctionSignature.hxx"
namespace ltnc {
	struct Stmt;
	
	struct Decl : public AstNode {
		Decl(const DebugInfo & debugInfo) : AstNode(debugInfo) {}	
		virtual ~Decl() = default;
	};

	struct DeclVar : public Decl {
		DeclVar(
			const DebugInfo & debugInfo,
			const VarId & varId,
			const TypeId & typeId)
		: 	Decl(debugInfo),
			varId(varId),
			typeId(typeId) {}

		DeclVar(
			const DebugInfo & debugInfo,
			const VarId & varId,
			const TypeId & typeId,
			const std::shared_ptr<Stmt> & assign)
		: 	Decl(debugInfo),
			varId(varId),
			typeId(typeId),
			assign(assign) {}
		
		VarId varId;
		TypeId typeId;
		std::shared_ptr<Stmt> assign;
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
			const std::vector<DeclVar> & members)
		:	Decl(debugInfo),
			typeId(typeId),
			members(members) {}
		
		TypeId typeId;
		std::vector<DeclVar> members;
	};
}