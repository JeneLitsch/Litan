#pragma once
#include "Config.hxx"
#include "CompilerError.hxx"
#include "Reporter.hxx"
#include "optimize/optimize.hxx"
#include "Source.hxx"

namespace ltn::c {
	ast::Program to_ast(
		std::vector<Source> sources,
		const Config & config,
		Reporter & reporter);

	std::string to_asm(
		const ast::Program & program,
		const Config & config,
		Reporter & reporter);
}