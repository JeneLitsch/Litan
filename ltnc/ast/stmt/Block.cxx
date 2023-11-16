#include "Block.hxx"

namespace ltn::c::ast::stmt {
	Block::Block(
		std::vector<stmt_ptr> statements,
		const SourceLocation & location) 
		: Statement(location)
		, statements(std::move(statements)) {}



	void Block::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Block::~Block() {}



	std::unique_ptr<Block> block(std::vector<stmt_ptr> statements, const SourceLocation & location) {
		return std::make_unique<Block>(std::move(statements), location);
	}
}