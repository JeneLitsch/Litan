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
		Decl(const NodeDebugInfo & debugInfo) : AstNode(debugInfo) {}
		Decl() : AstNode() {}
		virtual ~Decl() = default;
	};

	struct DeclVar : public Decl {
		DeclVar(
			const VarId & varId,
			const TypeId & typeId)
		: 	
			varId(varId),
			typeId(typeId) {}

		DeclVar(
			const VarId & varId,
			const TypeId & typeId,
			const std::shared_ptr<Stmt> & assign)
		: 	
			varId(varId),
			typeId(typeId),
			assign(assign) {}
		
		VarId varId;
		TypeId typeId;
		std::shared_ptr<Stmt> assign;
	};


	struct DeclFunction : public Decl {
		DeclFunction(
			const NodeDebugInfo & debugInfo,
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
		DeclStruct(const TypeId & typeId)
			: typeId(typeId) {}
		
		TypeId typeId;
		std::vector<DeclVar> members;
	};
}