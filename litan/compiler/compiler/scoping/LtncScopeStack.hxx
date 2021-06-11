#pragma once
#include "LtncScope.hxx"
#include <stack>
namespace ltnc {
	class ScopeStack {
	public:
		void addBlockScope();
		void addFunctionScope(const FxSignature & signature);
		void remove();
		Scope & get();
	private:
		std::stack<Scope> scope;
	};
}