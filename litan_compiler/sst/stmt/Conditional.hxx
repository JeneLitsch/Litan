#pragma once
#include "Statement.hxx"
#include "litan_compiler/sst/util/Conditional.hxx"

namespace ltn::c::sst::stmt {
    struct Conditional : sst::Conditional<Statement> {
		Conditional();

		virtual std::size_t temporary_alloc() const override;
		virtual std::size_t persistent_alloc() const override;
		
		virtual void accept(const StmtVisitor & visitor) const override;
    };
    
    std::unique_ptr<Conditional> conditional();
}