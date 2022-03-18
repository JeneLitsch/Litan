#pragma once
#include "ltnc/Backend.hxx"
#include "utils/FxTable.hxx"
#include "utils/GlobalTable.hxx"
#include "utils/MemberTable.hxx"
#include <sstream>
namespace ltn::c::compile {
	class LtnBackend : public Backend {
	public:
		virtual void compile(
			std::ostream & out,
			const Config & config,
			const ast::Program & program,
			Reporter & reporter) override;
		virtual ~LtnBackend() = default;
	private:

	};
	
}