#pragma once
#include "ltnc/Backend.hxx"
#include "FxTable.hxx"
#include "MemberTable.hxx"
#include <sstream>
namespace ltn::c::compile {
	class LtnBackend : public Backend {
	public:
		virtual void compile(
			const Config & config,
			const ast::Source & source) override;
		virtual void yield(std::ostream & out) override;
		virtual ~LtnBackend() = default;
	private:
		FxTable fxTable;
		MemberTable memberTable;
		std::stringstream buffer;
		std::size_t jumpMarkCounter = 0;
	};
	
}