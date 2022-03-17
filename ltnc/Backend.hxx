#pragma once
#include <ostream>
#include "ltnc/ast/Ast.hxx"
#include "Config.hxx"
#include "Reporter.hxx"
namespace ltn::c {
	class Backend {
	public:
		virtual void compile(
			std::ostream & out,
			const Config & config,
			const ast::Program & program,
			Reporter & reporter) = 0;
		virtual ~Backend() = default;
	};
}