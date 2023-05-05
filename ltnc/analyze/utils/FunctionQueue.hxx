#pragma once
#include <queue>
#include <tuple>
#include <set>
#include <optional>
#include "stdxx/reference.hxx"
#include "ltnc/ast/AST.hxx"

namespace ltn::c {
	struct Staged {
		stx::reference<const ast::Functional> fx;
		stx::optref<const std::vector<std::unique_ptr<ast::Var>>> captures;
		std::optional<Namespace> override_namespace = std::nullopt;
	};
	inline auto operator<=>(const Staged & l, const Staged & r) {
		return l.fx <=> r.fx;
	}
	

	class FunctionQueue {
	public:
		void stage_function(stx::reference<const ast::Functional> fx);
		void stage_function(Staged staged);
		std::optional<Staged> fetch_function();
	private:
		std::queue<Staged> queue;
		std::set<Staged> already_known;
	};
}