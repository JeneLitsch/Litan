#pragma once
#include "Statement.hxx"
#include "ltnc/sst/util/Conditional.hxx"

namespace ltn::c::sst::stmt {
    struct Conditional : sst::Conditional<Statement> {
		Conditional();

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		
		virtual void accept(const StmtVisitor & visitor) const override;
    };
    
    std::unique_ptr<Conditional> conditional();
}