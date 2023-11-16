#include <algorithm>
#include "Switch.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	Switch::Switch() : Statement{} {}



	std::uint64_t Switch::nested_alloc() const {
		return 0;
	}



	std::size_t Switch::direct_alloc() const {
		std::size_t nested = 0;
		std::size_t direct = 0;
		for(const auto & [c4se,stmt] : this->cases) {
			nested = std::max({
				nested,
				stmt->nested_alloc(),
				c4se->alloc()
			});
			direct += stmt->direct_alloc();
		}
		return nested + direct;
	}



	void Switch::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Switch::~Switch() {}



	std::unique_ptr<Switch> sw1tch() {
		return std::make_unique<Switch>();
	}
}