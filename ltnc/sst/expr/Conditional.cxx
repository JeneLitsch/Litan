#include "Conditional.hxx"

namespace ltn::c::sst::expr {
    Conditional::Conditional() 
        : sst::Conditional<Expression>{} {}



    void Conditional::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::uint64_t Conditional::alloc() const {
		const auto begin = std::begin(this->cases);
		const auto end = std::end(this->cases);
		const std::uint64_t start = else_branch ? else_branch->alloc() : 0;  
		const auto reduction = [] (const auto & value, const auto & elem) {
			const auto & [x, y] = elem;
			return std::max<std::uint64_t>({value, x->alloc(), y->alloc()});
		};
		
		return std::accumulate(begin, end, start, reduction);
	}


    
    std::unique_ptr<Conditional> conditional() {
        return std::make_unique<Conditional>();
    }
}