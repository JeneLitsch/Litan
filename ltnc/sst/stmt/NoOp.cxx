#include "NoOp.hxx"

namespace ltn::c::sst::stmt {
	NoOp::NoOp() : Statement{} {}
	

	
	std::size_t NoOp::nested_alloc() const {
		return 0;
	}



	std::size_t NoOp::direct_alloc() const {
		return 0;
	}



	void NoOp::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<NoOp> no_op() {
		return std::make_unique<NoOp>();
	}
}