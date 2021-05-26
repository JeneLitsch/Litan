#pragma once
#include "IExtension.hxx"

// just a smalle litan extension for demonstration the concept
// use ext::x 0 or alias for printing "Hello World"
class TextExtension : public ltn::IExtension{
public:
	virtual void call(std::uint8_t funct) override;
};