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
			: name(name), typeId(typeId) {}
		
		std::string name;
		TypeId typeId;
	};

	struct DeclStruct : public Decl {
		DeclStruct(const TypeId & typeId)
			: typeId(typeId) {}
		
		TypeId typeId;
		std::vector<std::shared_ptr<DeclVar>> members;
	};

	struct DeclFunction : public Decl {
		DeclFunction(
			FunctionSignature signature,
			std::shared_ptr<Stmt> body,
			bool inlined = false) 
			
			:		
			
			signature(signature),
			body(body),
			inlined(inlined) {}

		virtual ~DeclFunction() = default;
		FunctionSignature signature;
		std::shared_ptr<Stmt> body;
		bool inlined;
	};
}