#include "Conditional.hxx"

namespace ltn::c::sst::stmt {
    Conditional::Conditional() 
        : sst::Conditional<Statement>{} {}



	std::size_t Conditional::temporary_alloc() const {
		const auto begin = std::begin(this->cases);
		const auto end = std::end(this->cases);
		const std::uint64_t start = else_branch ? else_branch->temporary_alloc() : 0;  
		const auto reduction = [] (const auto & value, const auto & elem) {
			const auto & [x, y] = elem;
			return std::max<std::uint64_t>({value, x->alloc() + y->temporary_alloc()});
		};
		
		return std::accumulate(begin, end, start, reduction);
	}

	
	
	std::size_t Conditional::persistent_alloc() const {
		return 0;
	}



    void Conditional::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}

    
    std::unique_ptr<Conditional> conditional() {
        return std::make_unique<Conditional>();
    }
}