#pragma once
#include <cstdint>

void repeat(std::size_t repetition, const auto & body) {
	for(std::size_t i = 0; i < repetition; i++) {
		body();
	}
}

void repeat_1st(std::size_t repetition, const auto & body) {
	for(std::size_t i = 0; i < repetition; i++) {
		body(i==0);
	}
}