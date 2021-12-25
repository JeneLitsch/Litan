#pragma once
#include <ostream>
#include "ltnc/ast/Ast.hxx"
#include "Config.hxx"
namespace ltn::c {
	class Backend {
	public:
		virtual void compile(
			std::ostream & out,
			const Config & config,
			const std::vector<std::unique_ptr<ast::Functional>> & source) = 0;
		virtual ~Backend() = default;
	};
}