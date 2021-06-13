#pragma once
#include "LtncType.hxx"
#include <cstdint>
#include <set>
#include <memory>
#include "LtncVar.hxx"
#include "LtncSignature.hxx"
namespace ltnc {
	
	class Scope {
	public:
		Scope(Scope & scope);
		Scope(const FxSignature & signature);
		Scope();
		
		Var registerVar(const std::string & name, Type type);
		Var getVar(const std::string & name) const;
		std::uint32_t countVars() const;
		const FxSignature & getFxSignature() const;
	private:
		std::optional<FxSignature> fxSignature;
		std::set<Var, std::less<>> vars;
		Scope * prev;
	};

}