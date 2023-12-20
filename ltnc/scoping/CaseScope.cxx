#include "CaseScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	CaseScope::CaseScope(const Scope * outer) 
		: MajorScope { outer->get_namespace(), Qualifiers::just_const, context }
		, context {
			.fx_table = fx_table,
			.fx_queue = outer->get_context().fx_queue,
			.definition_table = outer->get_context().definition_table, 
			.member_table = outer->get_context().member_table, 
			.global_table = global_table,
			.custom_resolver = outer->get_context().custom_resolver,
		} {}
}