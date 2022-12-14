#include "FunctionQueue.hxx"

namespace ltn::c {
	void FunctionQueue::stage_function(stx::reference<const ast::Functional> fx) {
		StagedFx staged {
			.fx = fx,
		};
		if(this->already_known.contains(staged)) return;
		this->already_known.insert(staged);
		this->queue.push(std::move(staged));
	}


	void FunctionQueue::stage_template(
		stx::reference<const ast::FunctionTemplate> tmpl,
		std::vector<type::Type> arguments) {
		
		StagedTemplateFx staged {
			.tmpl = tmpl,
			.arguments = std::move(arguments),
		};
		if(this->already_known.contains(staged)) return;
		this->already_known.insert(staged);
		this->queue.push(std::move(staged));
	}




	std::optional<Staged> FunctionQueue::fetch_function() {
		if(this->queue.empty()) return std::nullopt;
		auto fx = this->queue.front();
		this->queue.pop();
		return fx;
	}
}