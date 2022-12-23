#include "candidate_picking.hxx"

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

	}



	const ast::Functional * pick_candidate(
		const std::vector<const ast::Functional *> & candidates,
		const std::vector<type::Type> & arguments) {

		constexpr auto qualify = [](const auto & matches) -> const ast::Functional * {
			if(matches.size() == 1) return matches[0];
			else return nullptr;	
		};
		
		const auto exact = pick_exact(candidates, arguments);
		if(!exact.empty()) return qualify(exact);
		const auto any_fallback = pick_any(candidates);
		return qualify(any_fallback);

	}
}