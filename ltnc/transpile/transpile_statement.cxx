#include "transpile.hxx"

namespace ltn::c {
	std::string transpile_statement(
		const sst::Statement & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		
		return sst::visit_statement(stmt, [&] (const auto & s) {
			return transpile_stmt(s, indentation, lang);
		});
	}



	std::string transpile_stmt(
		const sst::Block & block,
		unsigned indentation,
		const lang::Language & lang) {
		
		std::ostringstream oss;
		oss << lang.indent(indentation) << lang.block_begin() << "\n";
		for(const auto & stmt : block.statements) {
			oss << transpile_statement(*stmt, indentation+1, lang);
		}
		oss << lang.indent(indentation) << lang.block_end() << "\n";
		return oss.str();
	}



	std::string transpile_stmt(
		const sst::Return & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// RETURN\n";
	}



	std::string transpile_stmt(
		const sst::AssignLocal & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// ASSIGN LOCAL\n";
	}



	std::string transpile_stmt(
		const sst::AssignIndex & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// ASSIGN INDEX\n";

	}



	std::string transpile_stmt(
		const sst::AssignMember & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// ASSIGN MEMBER\n";
	}



	std::string transpile_stmt(
		const sst::AssignGlobal & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// ASSIGN GLOBAL\n";

	}



	std::string transpile_stmt(
		const sst::Throw & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// THROW\n";
	}



	std::string transpile_stmt(
		const sst::InitMember & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// INIT MEMBER\n";
	}



	std::string transpile_stmt(
		const sst::IfElse & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// IF ELSE\n";

	}



	std::string transpile_stmt(
		const sst::InfiniteLoop & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// LOOP\n";
	}



	std::string transpile_stmt(
		const sst::While & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// WHILE\n";
	}



	std::string transpile_stmt(
		const sst::For & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// FOR\n";
	}



	std::string transpile_stmt(
		const sst::NewVar & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// VAR\n";
	}



	std::string transpile_stmt(
		const sst::StmtSwitch & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// SWITCH\n";
	}


	std::string transpile_stmt(
		const sst::StatementExpression &,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// EXPR\n";

	}



	std::string transpile_stmt(
		const sst::DoNothing &,
		unsigned indentation,
		const lang::Language & lang) {
		return lang.indent(indentation) + "// NOTHING\n";
	}
}