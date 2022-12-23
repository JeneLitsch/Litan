#include "namespace_resolution.hxx"
#include "ltnc/type/check.hxx"
#include "candidate_picking.hxx"

namespace ltn::c {

	namespace {
		bool match(
			const ast::Functional & fx,
			const Namespace & full,
			const std::string_view name,
			const std::vector<type::Type> & arguments) {

			return
				fx.name == name &&
				fx.namespaze == full &&
				std::size(fx.parameters) == arguments.size();
		}



		bool match(
			const sst::Definition & definition,
			const Namespace & full,
			const std::string_view name) {

			return
				definition.name == name &&
				definition.namespaze == full;
		}


		
		bool match(
			const sst::Global & global,
			const Namespace & full,
			const std::string_view name) {

			return
				global.name == name &&
				global.namespaze == full;
		}



		bool match(
			const ast::FunctionTemplate & fx,
			const Namespace & full,
			const std::string_view name,
			const std::size_t function_parameters,
			const std::size_t template_parameters) {

			return
				fx.fx->name == name &&
				fx.fx->namespaze == full &&
				std::size(fx.fx->parameters) == function_parameters &&
				std::size(fx.template_parameters) == template_parameters;
		}



		template<typename DeclNode>
		void resolve_rec(
			std::vector<const DeclNode *> & candidates,
			const std::vector<const DeclNode *> & declarations,
			const Namespace & from,
			const Namespace & to,
			const std::string_view name,
			const auto & ... additional) {

			for(const auto & fx : declarations) {
				if(match(*fx, from + to, name, additional...)) {
					candidates.push_back(fx);
				}
			}

			if(!candidates.empty()) {
				return;
			}
			
			if(!from.empty()) {
				Namespace outer = from;
				outer.pop_back();

				return resolve_rec(
					candidates,
					declarations,
					outer,
					to,
					name,
					additional...);
			}
		}



		template<typename DeclNode>
		std::vector<const DeclNode *> resolve_candidates(
			const std::vector<const DeclNode *> & decls,
			const Namespace & from,
			const Namespace & to,
			const std::string_view name,
			const auto & ... additional) {

			std::vector<const DeclNode *> candidates;

			if(to.is_absolute()) {
				for(const auto & d : decls) {
					if(match(*d, to, name, additional...)) {
						candidates.push_back(d);
					}
				}
				return candidates;
			}
		
			resolve_rec(candidates, decls, from, to, name, additional...);
			return candidates;
		}




	}



	const ast::Functional * resolve(
		const std::vector<const ast::Functional *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::vector<type::Type> & arguments) {
		
		const auto candidates = resolve_candidates(functions, from, to, name, arguments);
		return pick_candidate(candidates, arguments);
	}



	const sst::Definition * resolve(
		const std::vector<const sst::Definition *> & definition,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name) {

		return pick_candidate(resolve_candidates(definition, from, to, name));
	}



	const sst::Global * resolve(
		const std::vector<const sst::Global *> & globals,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name) {
		return pick_candidate(resolve_candidates(globals, from, to, name));
	}



	const ast::FunctionTemplate * resolve(
		const std::vector<const ast::FunctionTemplate *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::size_t function_parameters,
		const std::size_t template_parameters) {
		
		const auto candidates = resolve_candidates(functions, from, to, name, function_parameters, template_parameters);
		return pick_candidate(candidates);
	}
}