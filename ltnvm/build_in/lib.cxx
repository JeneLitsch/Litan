#include "lib.hxx"
#include "ltnvm/Exception.hxx"
#include "litan_c_api.h"
#include <filesystem>
#include "stdxx/iife.hxx"

namespace ltn::vm::build_in {
	namespace {
		std::filesystem::path lib_dir = "/usr/local/bin/ltn_libs";
	}

	Value lib_open(VmCore & core) {
		auto name = core.stack.pop();
		if(!is_string(name)) {
			throw Exception{Exception::Type::INVALID_ARGUMENT, ""};
		}
		auto lib = stx::iife([&] {
			const auto & lib_name = core.heap.read<String>(name.u); 
			if(std::filesystem::exists(lib_name)) {
				return stx::dynamic_lib { lib_name };
			}
			else {
				return stx::dynamic_lib { lib_dir/lib_name };
			}
		});
		return value::library(core.heap.alloc(std::move(lib)));
	}



	Value lib_close(VmCore & core) {
		auto lib = core.stack.pop();
		if(!is_library(lib)) {
			throw Exception{Exception::Type::INVALID_ARGUMENT, ""};
		}
		// TODO
		return value::null;
	}



	Value lib_get_fx(VmCore & core) {
		auto fx_name = core.stack.pop();
		auto lib = core.stack.pop();
		if(!is_library(lib)) {
			throw Exception{Exception::Type::INVALID_ARGUMENT, ""};
		}
		if(!is_string(fx_name)) {
			throw Exception{Exception::Type::INVALID_ARGUMENT, ""};
		}
		auto fx_ptr 
			= core.heap.read<Library>(lib.u)
			. get_if_fx<void, ltn_CApi *>(core.heap.read<String>(fx_name.u));
		if(!fx_ptr) {
			throw Exception{Exception::Type::INVALID_MEMBER_ACCESS, ""};
		}
		return value::library_fx(core.heap.alloc(LibraryFx {
			.fx_ptr = fx_ptr,
			.arity = 0,
			.library = lib,
		}));
	}
}