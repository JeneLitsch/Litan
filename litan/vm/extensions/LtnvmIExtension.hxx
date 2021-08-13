#pragma once
#include "LtnvmEnvironment.hxx"
#include "LtnExtSlot.hxx"
namespace ltn::vm {
	class IExtension {
	public:
		virtual void call(std::uint8_t func) = 0;
		void setEnvironsment(Environment & env) {
			this->env = &env;
		}
	protected:
		Environment * env;
	};
}