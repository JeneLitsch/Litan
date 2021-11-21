#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		
	}
	
	std::string makeJumpId(const std::string_view name, CompilerInfo & info) {
		std::stringstream ss;
		ss << name << info.jumpMarkCounter++;
		return ss.str();
	}

	StmtCode ifElse(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope) {
		Scope ifScope{&scope};
		Scope elseScope{&scope};
		const auto idIfEnd = makeJumpId("IF_END", info);
		const auto condition = expression(*stmt.condition, info, scope);
		const auto ifBranch = statement(*stmt.ifBranch, info, ifScope);
		if(stmt.elseBranch) {
			const auto elseBranch = statement(*stmt.elseBranch, info, elseScope);
			const auto idElse = makeJumpId("IF_ELSE", info);
			std::stringstream ss;
			ss << condition.code;
			ss << inst::ifelse(idElse);

			ss << ifBranch.code;
			ss << inst::jump(idIfEnd);

			ss << inst::jumpmark(idElse);
			ss << elseBranch.code;
			ss << inst::jump(idIfEnd);

			ss << inst::jumpmark(idIfEnd);
			return {ss.str()};
		}
		else {
			std::stringstream ss;
			ss << condition.code;
			ss << inst::ifelse(idIfEnd);

			ss << ifBranch.code;
			ss << inst::jumpmark(idIfEnd);
			return {ss.str()};
		}

	}
}