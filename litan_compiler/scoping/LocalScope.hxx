#pragma once
#include "Scope.hxx"

namespace ltn::c {
	class LocalScope : public Scope {
	public:
		virtual Variable declare_variable(const std::string & name, const SourceLocation & location) override;
	protected:
		std::unordered_map<std::string, Variable> vars;
	};
}