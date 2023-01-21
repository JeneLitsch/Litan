#pragma once
#include "stdxx/dynamic_lib.hxx"
#include "litan_c_api.h"

namespace ltn::vm {
	using Library = stx::dynamic_lib;

	inline Library clone(const Library &) {
		throw std::runtime_error{"Cannot clone IStream."};
	}

	struct LibraryFx {
		void(* fx_ptr)(CApi *);
		std::size_t arity;
	};

	inline LibraryFx clone(const LibraryFx & fx) {
		return fx;
	}
}