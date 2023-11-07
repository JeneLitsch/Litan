#include "Iife.hxx"
#include "ltnc/sst/stmt/Statement.hxx"

namespace ltn::c::sst {
	Iife::Iife(std::string return_label, std::unique_ptr<Statement> stmt) 
		: return_label{return_label}
		, stmt(std::move(stmt)) {}



	std::uint64_t Iife::alloc() const {
		return this->stmt->direct_alloc() + this->stmt->nested_alloc();
	}
}