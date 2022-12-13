#pragma once
#include <queue>
#include <set>
#include <optional>
#include "stdxx/reference.hxx"
#include "ltnc/sst/SST.hxx"

namespace ltn::c {
	struct StagedFx {
		stx::reference<const sst::Functional> fx;
	};
	inline auto operator<=>(const StagedFx & l, const StagedFx & r) {
		return  &*l.fx <=> &*r.fx;
	}
	
	
	
	struct StagedTemplateFx {
		stx::reference<const sst::FunctionTemplate> tmpl;
		std::vector<type::Type> arguments;
	};
	inline auto operator<=>(const StagedTemplateFx & l, const StagedTemplateFx & r) {
		auto l_fx = &*l.tmpl;
		auto r_fx = &*r.tmpl;
		return std::tie(l_fx, l.arguments) <=> std::tie(r_fx, r.arguments);
	}

	using Staged = std::variant<StagedFx,StagedTemplateFx>;

	class FunctionQueue {
	public:
		void stage_function(stx::reference<const sst::Functional> fx);
		void stage_template(stx::reference<const sst::FunctionTemplate> tmpl, std::vector<type::Type> arguments);
		std::optional<Staged> fetch_function();
	private:
		std::queue<Staged> queue;
		std::set<Staged> already_known;
	};
}