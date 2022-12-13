#include "compile.hxx"

namespace ltn::c {
	std::unique_ptr<sst::Global> analyze_global(const ast::Global & node, CompilerInfo & info) {
		auto glob =	stx::make_unique<sst::Global>(node.location, node.name, node.namespaze, node.type);
		MajorScope scope{node.namespaze, true};
		glob->expr = node.expr ? analyze_expression(*node.expr, info, scope) : nullptr;
		return glob;
	}
	std::unique_ptr<sst::Definition> analyze_definition(const ast::Definition & node, CompilerInfo & info) {
		auto def = stx::make_unique<sst::Definition>(node.location, node.name, node.namespaze, node.type);
		MajorScope scope{node.namespaze, true};
		def->expr = node.expr ? analyze_expression(*node.expr, info, scope) : nullptr;
		return def;
	}
}