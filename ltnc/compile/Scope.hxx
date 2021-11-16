#pragma once
#include "FxSignature.hxx"
namespace ltn::c::compile {
	class Scope {
	public:
		Scope(const Scope * parent = nullptr);
		



	
	private:
		const Scope * parent;
	};
}