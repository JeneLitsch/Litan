#include "Block.hxx"

namespace ltn::c::sst::stmt {
	Block::Block(
		std::vector<stmt_ptr> statements) 
		: Statement{}
		, statements(std::move(statements)) {}



	std::size_t Block::temporary_alloc() const {
		std::size_t temporary = 0;
		std::size_t persistent = 0;
		for(const auto & stmt : this->statements) {
			temporary = std::max(temporary, stmt->temporary_alloc());
			persistent += stmt->persistent_alloc();
		}
		return temporary + persistent;
	}
	


	std::size_t Block::persistent_alloc() const {
		// No persistent allocation,
		// because the block discards all variables at the end
		return 0;
	}



	void Block::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Block> block(std::vector<stmt_ptr> statements) {
		return std::make_unique<Block>(std::move(statements));
	}
}