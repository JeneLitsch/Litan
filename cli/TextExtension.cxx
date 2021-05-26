#include "TextExtension.hxx"
#include <iostream>
void TextExtension::call(std::uint8_t funct) {
	switch (funct)
	{
	case 0: std::cout << "Hello World" << std::endl; break;
	}
}
