#include "NoOp.hxx"

namespace ltn::c::sst::stmt {
	NoOp::NoOp() : Statement{} {}
	

	
	std::size_t NoOp::temporary_alloc() const {
		return 0;
	}



	std::size_t NoOp::persistent_alloc() const {
		return 0;
	}



	void NoOp::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<NoOp> no_op() {
		return std::make_unique<NoOp>();
	}
}