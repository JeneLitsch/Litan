#include "LtncScopeStack.hxx"

void ltnc::ScopeStack::addBlockScope() {
	this->scope.emplace(this->get());
}

void ltnc::ScopeStack::addFunctionScope(const FxSignature & signature) {
	this->scope.emplace(signature);
}

void ltnc::ScopeStack::remove() {
	this->scope.pop();
}

ltnc::Scope & ltnc::ScopeStack::get() {
	return this->scope.top();
}

