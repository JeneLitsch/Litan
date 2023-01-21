#pragma once
#include "stdxx/dynamic_lib.hxx"
#include "litan_c_api.h"

namespace ltn::vm {
	using Library = stx::dynamic_lib;

	inline Library clone(const Library &) {
		throw std::runtime_error{"Cannot clone Library."};
	}



	struct LibraryFx {
		void(* fx_ptr)(ltn_CApi *);
		std::size_t arity;
		Value library;
	};

	inline LibraryFx clone(const LibraryFx & fx) {
		return fx;
	}



	class LibraryObj {
	public:
		LibraryObj(ltn_CObject obj, Value library)
			: obj{obj}
			, library{library} {}

		LibraryObj(const LibraryObj &) = delete;
		LibraryObj & operator=(const LibraryObj &) = delete;
		
		LibraryObj(LibraryObj && other) {
			this->obj.ptr = other.obj.ptr;
			this->obj.deleter = other.obj.deleter;
			other.obj.ptr = nullptr;
			other.obj.deleter = nullptr;
		}
		
		LibraryObj & operator=(LibraryObj && other) {
			this->obj.ptr = other.obj.ptr;
			this->obj.deleter = other.obj.deleter;
			other.obj.ptr = nullptr;
			other.obj.deleter = nullptr;
			return *this;
		}

		~LibraryObj() {
			if(obj.ptr && obj.deleter) {
				obj.deleter(obj.ptr);
			}
		}

		const ltn_CObject & get() const {
			return obj;
		}

	private:
		ltn_CObject obj;

	public:
		Value library;
	};

	inline LibraryObj clone(const LibraryObj &) {
		throw std::runtime_error{"Cannot clone LibraryObj."};
	}
}