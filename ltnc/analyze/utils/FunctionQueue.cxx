#include "FunctionQueue.hxx"

namespace ltn::c {
	void FunctionQueue::stage_function(
		stx::reference<const ast::Functional> fx) {
		this->stage_function(Staged {
			.fx = fx,
		});
	}



	void FunctionQueue::stage_function(Staged staged) {
		if(this->already_known.contains(staged)) return;
		this->already_known.insert(staged);
		this->queue.push(std::move(staged));
	};



	std::optional<Staged> FunctionQueue::fetch_function() {
		if(this->queue.empty()) return std::nullopt;
		auto fx = this->queue.front();
		this->queue.pop();
		return fx;
	}
}