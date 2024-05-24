#include "Scope.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/analyze/error.hxx"

#include "ltnc/analyze/utils/FunctionQueue.hxx"

namespace ltn::c {
	void Scope::set_return(const std::string & return_point) {
		this->return_point = return_point;
	}



	void Scope::require_function(stx::reference<const ast::decl::Function> fx) {
		return this->get_context().fx_queue.stage_function(fx);
	}

	
	
	void Scope::require_function(StagedFunction staged) {
		return this->get_context().fx_queue.stage_function(staged);
	}



	const std::vector<const ast::decl::Function *> & Scope::get_all_functions() const {
		return this->get_context().fx_table.get_symbols();
	}
}

