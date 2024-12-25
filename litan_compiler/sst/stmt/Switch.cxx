#include <algorithm>
#include "Switch.hxx"
#include "litan_compiler/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	Switch::Switch() : Statement{} {}



	std::uint64_t Switch::temporary_alloc() const {
		std::size_t temporary = 0;
		std::size_t persistent = 0;
		for(const auto & [c4se,stmt] : this->cases) {
			temporary = std::max({
				temporary,
				stmt->temporary_alloc(),
				c4se->alloc()
			});
			persistent += stmt->persistent_alloc();
		}
		return temporary + persistent;
	}



	std::size_t Switch::persistent_alloc() const {
		return 0;
	}



	void Switch::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Switch::~Switch() {}



	std::unique_ptr<Switch> sw1tch() {
		return std::make_unique<Switch>();
	}
}