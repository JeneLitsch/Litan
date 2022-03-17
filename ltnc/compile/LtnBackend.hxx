#pragma once
#include "ltnc/Backend.hxx"
#include "utils/FxTable.hxx"
#include "utils/EnumTable.hxx"
#include "MemberTable.hxx"
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

		std::size_t jump_mark_counter = 0;
	};
	
}