#pragma once

#include "litan_vm/objects/StaticObject.hxx"


namespace ltn::vm {
	class ArrayType : public StaticObject {
	public:
		virtual Value get_member(VMCore & core, std::uint64_t id) const override;
		Value get_nonstatic_member(VMCore & core, std::uint64_t id) const;
	};
}