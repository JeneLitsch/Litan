#include "compile.hxx"
#include <iostream>
#include "build_in.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer compile_except(	
			const sst::misc::Except & except,
			const Label& label_except) {
			
			InstructionBuffer buf;
			buf << inst::label(label_except.to_string());
			buf << compile_statement(*except.body);
			buf << inst::null();
			buf << inst::retvrn();
			return buf;
		}
	}



	InstructionBuffer compile_function(const sst::decl::Function & fx) {
		InstructionBuffer buf;

		const auto except_label = derive_except(fx.label); 
		
		buf << inst::label(fx.label.to_string());

		if(fx.except) {
			buf << inst::trY(except_label.to_string());
		} 
		
		if(fx.qualifiers.is_coroutine) {
			buf << inst::co_dump();
		}

		buf << compile_statement(*fx.body);
		buf << inst::null();
		
		if(fx.qualifiers.is_coroutine) {
			buf << inst::co_retvrn();
		}
		else {
			buf << inst::retvrn();
		}

		if(fx.except) {
			buf << compile_except(*fx.except, except_label);
		} 
		
		return buf;
	}
}