#pragma once

#include "ltnc_core/Ltnc.hxx"
#include "ltna/Ltna.hxx"
#include "ltnvm/LtnVM.hxx"
#include "ltnc/compile/LtnBackend.hxx"

namespace ltn {
	using Ltnc = c::Ltnc;
	using Ltna = a::Ltna;
	using LtnVm = vm::LtnVM;

	using LtnBackend = c::compile::LtnBackend;
	
	using Value = vm::Value;
	using External = vm::ext::External;
	using Api = vm::ext::Api;
}