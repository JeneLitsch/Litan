#include "candidate_picking.hxx"
#include "ltnc/analyze/conversion.hxx"

namespace ltn::c {
	namespace {
		bool match_exact(
			const ast::Functional & candidate,
			const std::vector<type::Type> & arguments) {
			
			for(std::size_t i = 0; i < arguments.size(); ++i) {
				if(candidate.parameters[i].type.type != arguments[i]) {
					return false;
				}
			}
			
			return true;
		}



		bool match_partial(
			const ast::Functional & candidate,
			const std::vector<type::Type> & arguments) {
			
			for(std::size_t i = 0; i < arguments.size(); ++i) {
				if(!is_convertible(arguments[i], candidate.parameters[i].type.type)) {
					return false;
				}
			}
			
			return true;
		}



		bool match_any(const ast::Functional & candidate) {
			
			for(std::size_t i = 0; i < candidate.parameters.size(); ++i) {
				if(!type::is_any(candidate.parameters[i].type.type)) {
					return false;
				}
			}
			
			return true;
		}



		auto pick_exact(
			const std::vector<const ast::Functional *> & candidates,
			const std::vector<type::Type> & arguments) {
			std::vector<const ast::Functional *> matches;
			for(const auto & candidate : candidates) {
				if(match_exact(*candidate, arguments)) {
					matches.push_back(candidate);
				}
			}
			return matches;
		}



		auto pick_partial(
			const std::vector<const ast::Functional *> & candidates,
			const std::vector<type::Type> & arguments) {
			std::vector<const ast::Functional *> matches;
			for(const auto & candidate : candidates) {
				if(match_partial(*candidate, arguments) && !match_any(*candidate)) {
					matches.push_back(candidate);
				}
			}
			return matches;
		}



		auto pick_any(
			const std::vector<const ast::Functional *> & candidates) {
			std::vector<const ast::Functional *> matches;
			for(const auto & candidate : candidates) {
				if(match_any(*candidate)) {
					matches.push_back(candidate);
				}
			}
			return matches;
		}

		constexpr auto qualify = [](const auto & candidates)
			-> std::remove_reference_t<decltype(candidates[0])> {
			if(candidates.size() == 1) return candidates[0];
			else return nullptr;
		};
	}



	const ast::Functional * pick_candidate(
		const std::vector<const ast::Functional *> & candidates,
		const std::vector<type::Type> & arguments) {

		const auto exact = pick_exact(candidates, arguments);
		if(!exact.empty()) return qualify(exact);
		const auto partial = pick_partial(candidates, arguments);
		if(!partial.empty()) return qualify(partial);
		const auto any_fallback = pick_any(candidates);
		return qualify(any_fallback);

	}



	const ast::Functional * pick_candidate_exact(
		const std::vector<const ast::Functional *> & candidates,
		const std::vector<type::Type> & arguments) {
		const auto exact = pick_exact(candidates, arguments);
		if(!exact.empty()) return qualify(exact);
	}



	const sst::Definition * pick_candidate(
		const std::vector<const sst::Definition *> & candidates) {
		return qualify(candidates);
	}



	const sst::Global * pick_candidate(
		const std::vector<const sst::Global *> & candidates) {
		return qualify(candidates);
	}



	const ast::FunctionTemplate * pick_candidate(
		const std::vector<const ast::FunctionTemplate *> & candidates) {
		return qualify(candidates);
	}
}