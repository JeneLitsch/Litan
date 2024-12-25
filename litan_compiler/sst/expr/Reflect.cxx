#include "Reflect.hxx"

namespace ltn::c::sst::expr {
	Reflect::Reflect(Query query, Addr address)
		: query{std::move(query)}
		, address{address} {}



	std::uint64_t Reflect::alloc() const {
		return 0;
	}



	std::unique_ptr<Reflect> reflect(Reflect::Query query, Reflect::Addr address) {
		return std::make_unique<Reflect>(std::move(query), std::move(address));
	}
}