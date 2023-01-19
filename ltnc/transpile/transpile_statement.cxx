#include "transpile.hxx"

namespace ltn::c {
	std::string transpile_statement(
		const sst::Statement & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		
		sst::visit_statement(stmt, [&](const auto & s) {
			return transpile_stmt(s, indentation, lang);
		});
	}



	std::string transpile_stmt(
		const sst::Block & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// BLOCK";
	}



	std::string transpile_stmt(
		const sst::Return & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// RETURN";
	}



	std::string transpile_stmt(
		const sst::AssignLocal & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// ASSIGN LOCAL";
	}



	std::string transpile_stmt(
		const sst::AssignIndex & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// ASSIGN INDEX";

	}



	std::string transpile_stmt(
		const sst::AssignMember & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// ASSIGN MEMBER";
	}



	std::string transpile_stmt(
		const sst::AssignGlobal & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// ASSIGN GLOBAL";

	}



	std::string transpile_stmt(
		const sst::Throw & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// THROW";
	}



	std::string transpile_stmt(
		const sst::InitMember & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// INIT MEMBER";
	}



	std::string transpile_stmt(
		const sst::IfElse & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// IF ELSE";

	}



	std::string transpile_stmt(
		const sst::InfiniteLoop & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// LOOP";
	}



	std::string transpile_stmt(
		const sst::While & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// WHILE";
	}



	std::string transpile_stmt(
		const sst::For & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// FOR";
	}



	std::string transpile_stmt(
		const sst::NewVar & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// VAR";
	}



	std::string transpile_stmt(
		const sst::StmtSwitch & stmt,
		unsigned indentation,
		const lang::Language & lang) {
		return "// SWITCH";
	}
}