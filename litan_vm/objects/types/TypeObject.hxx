#pragma once
#include "litan_vm/objects/StaticObject.hxx"

namespace ltn::vm {
	class TypeObject : public StaticObject {
		virtual void stringify(VMCore &, std::ostream & oss, bool) override {
			oss << "<Type>";
		}
	};
}