#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		auto makeJumpId(const std::string_view name, CompilerInfo & info) {
			std::stringstream ss;
			ss << name << info.jumpMarkCounter++;
			return ss.str();
		}
	}

	StmtCode ifElse(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope) {
		const auto idIf = makeJumpId("IF", info);
		const auto idIfEnd = makeJumpId("IF_END", info);
		const auto condition = compile::expression(*stmt.condition, info, scope);
		const auto ifBranch = compile::statement(*stmt.ifBranch, info, scope);
		if(stmt.elseBranch) {
			const auto elseBranch = compile::statement(*stmt.elseBranch, info, scope);
			const auto idElse = makeJumpId("IF_END", info);
			std::stringstream ss;
			ss << condition.code;
			ss << inst::iF;
			ss << inst::jump(idIf);
			ss << inst::jump(idElse);

			ss << inst::jumpmark(idIf);
			ss << ifBranch.code;
			ss << inst::jump(idIfEnd);

			ss << inst::jumpmark(idElse);
			ss << elseBranch.code;
			ss << inst::jump(idElse);

			ss << inst::jumpmark(idIfEnd);
			return {ss.str()};
		}
		else {
			std::stringstream ss;
			ss << condition.code;
			ss << inst::iF;
			ss << inst::jump(idIf);
			ss << inst::jump(idIfEnd);

			ss << inst::jumpmark(idIf);
			ss << ifBranch.code;
			ss << inst::jump(idIfEnd);
			
			ss << inst::jumpmark(idIfEnd);
			return {ss.str()};
		}

	}
}