#include "ltn/casts.hxx"
namespace ltn::c {
	template<typename Parent>
	auto pick_branch(bool is_true, Parent & parent) {
		if(is_true) {
			return std::move(parent.if_branch);
		}
		else {
			return std::move(parent.else_branch);
		}
	}


	template<typename Condition>
	auto truthy(Condition & condition) {
		return static_cast<bool>(condition.value);
	}



	template<>
	inline auto truthy<ast::String>(ast::String &) {
		return true;
	}



	template<>
	inline auto truthy<ast::Array>(ast::Array &) {
		return true;
	}



	template<>
	inline auto truthy<ast::Null>(ast::Null &) {
		return false;
	}



	template<typename Condition>
	bool is_truthy(ast::Expression & condition) {
		if(auto * c = as<Condition>(condition)) {
			return truthy<Condition>(*c);
		}
		return false;
	}



	template<typename Condition, typename Parent>
	auto pre_decide(Parent & parent) -> decltype(parent.if_branch) {
		if(auto * condition = as<Condition>(*parent.condition)) {
			bool is_always_true = truthy<Condition>(*condition);
			return pick_branch(is_always_true, parent);
		}
		return nullptr;
	} 


	
}