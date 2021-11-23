#pragma once
#include <ostream>
#include "ltnc/ast/Source.hxx"
#include "Config.hxx"
namespace ltn::c {
	class Backend {
	public:
		virtual void compile(
			const Config & config,
			const ast::Source & source) = 0;
		virtual void yield(std::ostream & out) = 0;
		virtual ~Backend() = default;
	};
}