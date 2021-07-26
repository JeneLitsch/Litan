#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LtncType.hxx"
#include "LtncVar.hxx"
#include "LtncFunctionSignature.hxx"
namespace ltnc {
	struct Stmt;

	struct Decl  {
		Decl() {}
		virtual ~Decl() = default;
	};

	struct DeclVar : public Decl {
		DeclVar(
			const std::string & name,
			const TypeId & typeId)
		: 	
			name(name),
			typeId(typeId) {}

		DeclVar(
			const std::string & name,
			const TypeId & typeId,
			const std::shared_ptr<Stmt> & assign)
		: 	
			name(name),
			typeId(typeId),
			assign(assign) {}
		
		std::string name;
		TypeId typeId;
		std::shared_ptr<Stmt> assign;
	};


	struct DeclFunction : public Decl {
		DeclFunction(
			FunctionSignature signature,
			std::shared_ptr<Stmt> body) 
		:	signature(signature),
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