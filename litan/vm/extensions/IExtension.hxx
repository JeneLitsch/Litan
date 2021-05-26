#pragma once
#include "Environment.hxx"
namespace ltn{
	class IExtension {
	public:
		enum class Slot{_0 = 0, _1, _2, _3, _4, _5, _6, _7};
		virtual void call(std::uint8_t func) = 0;
		void setEnvironsment(Environment & env) {
			this->env = &env;
		}
	protected:
		Environment * env;
	};
}