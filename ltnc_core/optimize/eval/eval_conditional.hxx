#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	template<typename Condition, typename Parent>
	auto pick_branch(Condition & condition, Parent & parent) {
		if(static_cast<bool>(condition.value)) {
			return std::move(parent.if_branch);
		}
		else {
			return std::move(parent.else_branch);
		}
	}


	template<typename Parent>
	auto pick_branch(ast::String &, Parent & parent) {
		return std::move(parent.if_branch);
	}



	template<typename Parent>
	auto pick_branch(ast::Array &, Parent & parent) {
		return std::move(parent.if_branch);
	}



	template<typename Parent>
	auto pick_branch(ast::Null &, Parent & parent) {
		return std::move(parent.if_branch);
	}



	template<typename Condition, typename Parent>
	auto pre_decide(Parent & parent) -> decltype(parent.if_branch) {
		if(auto * condition = as<Condition>(*parent.condition)) {
			return pick_branch(*condition, parent);
		}
		return nullptr;
	} 
}