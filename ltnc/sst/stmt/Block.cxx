#include "Block.hxx"

namespace ltn::c::sst::stmt {
	Block::Block(
		std::vector<stmt_ptr> statements) 
		: Statement{}
		, statements(std::move(statements)) {}



	std::size_t Block::nested_alloc() const {
		std::size_t nested = 0;
		std::size_t direct = 0;
		for(const auto & stmt : this->statements) {
			nested = std::max(nested, stmt->nested_alloc());
			direct += stmt->direct_alloc();
		}
		return nested + direct;
	}
	


	std::size_t Block::direct_alloc() const {
		return 0;
	}



	void Block::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Block> block(std::vector<stmt_ptr> statements) {
		return std::make_unique<Block>(std::move(statements));
	}
}