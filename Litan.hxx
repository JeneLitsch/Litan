#pragma once

#include "ltnc/Ltnc.hxx"
#include "ltna/Ltna.hxx"
#include "ltnvm/LtnVM.hxx"

namespace ltn {
	using Ltnc = c::Ltnc;
	using Ltna = a::Ltna;
	using LtnVm = vm::LtnVM;

	using Value = vm::Value;
	
	using External = vm::ext::External;
	using Api = vm::ext::Api;
}