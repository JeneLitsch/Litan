#pragma once
#include "ltnc_core/Backend.hxx"
#include "ltnc_core/compile/utils/CompilerInfo.hxx"
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