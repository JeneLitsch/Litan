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


	struct DeclTemplate : public Decl {
		DeclTemplate(
			const DebugInfo & debugInfo,
			std::vector<std::string> && placeholders) 
		:	Decl(debugInfo),
			placeholders(std::move(placeholders)) {}

		virtual ~DeclTemplate() = default;
		std::vector<std::string> placeholders;
	};

	struct DeclTemplateFunction : public DeclTemplate {
		DeclTemplateFunction(
			const DebugInfo & debugInfo,
			std::vector<std::string> && placeholders,
			std::unique_ptr<DeclFunction> && decl) 
		:	DeclTemplate(debugInfo, std::move(placeholders)),
			decl(std::move(decl)) {}

		virtual ~DeclTemplateFunction() = default;
		std::unique_ptr<DeclFunction> decl;
	};

	struct DeclTemplateStruct : public DeclTemplate {
		DeclTemplateStruct(
			const DebugInfo & debugInfo,
			std::vector<std::string> && placeholders,
			std::unique_ptr<DeclStruct> && decl) 
		:	DeclTemplate(debugInfo, std::move(placeholders)),
			decl(std::move(decl)) {}

		virtual ~DeclTemplateStruct() = default;
		std::unique_ptr<DeclStruct> decl;
	};
}