#include "compile.hxx"
#include "utils/Instructions.hxx"
#include <sstream>
namespace ltn::c::compile {
	namespace {
		std::string jump_else(const std::string & id) {
			return id + "_ELSE";
		}

		std::string jump_end(const std::string & id) {
			return id + "_END";
		}
	}

	std::string conditional(
		const std::string & name,
		const std::string_view condition,
		const std::string_view if_branch,
		std::optional<const std::string_view> else_branch) {

		if(else_branch) {
			const auto to_else = jump_else(name); 
			const auto to_end = jump_end(name);
			
			std::ostringstream ss;
			ss << condition;
			ss << inst::ifelse(to_else);

			ss << if_branch;
			ss << inst::jump(to_end);

			ss << inst::jumpmark(to_else);
			ss << *else_branch;

			ss << inst::jumpmark(to_end);

			return ss.str();
		}

		else {
			const auto to_else = jump_else(name); 

			std::ostringstream ss;
			ss << condition;
			ss << inst::ifelse(to_else);

			ss << if_branch;
			ss << inst::jumpmark(to_else);

			return ss.str();
		}
	}
}