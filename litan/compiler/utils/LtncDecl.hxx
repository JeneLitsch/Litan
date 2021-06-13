#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LtncType.hxx"
#include "LtncVar.hxx"
#include "LtncSignature.hxx"
namespace ltnc {
	struct Stmt;

	struct Decl  {
		Decl() {}
		virtual ~Decl() = default;
	};

	struct DeclVar : public Decl {
		DeclVar(const std::string & name, Type type)
			: name(name), type(type) {}
		std::string name;
		Type type;
	};

	struct DeclStruct : public Decl {
		DeclStruct(const std::string & name)  {
			this->name = name;
		}
		std::string name;
		std::vector<std::shared_ptr<DeclVar>> members;
	};

	struct DeclFunction : public Decl {
		DeclFunction(
			FxSignature signature,
			std::shared_ptr<Stmt> body,
			bool inlined = false) 
			
			:		
			
			signature(signature),
			body(body),
			inlined(inlined) {}

		virtual ~DeclFunction() = default;
		FxSignature signature;
		std::shared_ptr<Stmt> body;
		bool inlined;
	};
}