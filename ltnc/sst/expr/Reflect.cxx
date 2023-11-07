#include "Reflect.hxx"

namespace ltn::c::sst {
	Reflect::Reflect(Query query, Addr address)
		: query{std::move(query)}
		, address{address} {}



	std::uint64_t Reflect::alloc() const {
		return 0;
	}
}