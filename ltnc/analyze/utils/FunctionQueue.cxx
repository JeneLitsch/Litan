#include "FunctionQueue.hxx"

namespace ltn::c {
	void FunctionQueue::stage_function(
		stx::reference<const ast::decl::Function> fx) {
		this->stage_function(StagedFunction {
			.fx = fx,
			.captures = {},
			.override_namespace = std::nullopt,
		});
	}



	void FunctionQueue::stage_function(StagedFunction staged) {
		if(this->already_known.contains(staged)) return;
		this->already_known.insert(staged);
		this->queue.push(std::move(staged));
	}



	std::optional<StagedFunction> FunctionQueue::fetch_function() {
		if(this->queue.empty()) return std::nullopt;
		auto fx = this->queue.front();
		this->queue.pop();
		return fx;
	}
}