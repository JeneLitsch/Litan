#pragma once
#include "ltnc/Backend.hxx"
#include "FxTable.hxx"
#include "MemberTable.hxx"
#include <sstream>
namespace ltn::c::compile {
	class LtnBackend : public Backend {
	public:
		virtual void compile(
			std::ostream & out,
			const Config & config,
			const std::vector<std::unique_ptr<ast::Functional>> & source,
			Reporter & reporter) override;
		virtual ~LtnBackend() = default;
	private:
		FxTable fx_table;
		MemberTable memberTable;
		std::size_t jump_mark_counter = 0;
	};
	
}