#include "compile.hxx"
#include <iostream>
#include "build_in.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer compile_body(const auto & fx) {
			InstructionBuffer buf;
			if(fx.body) {
				const auto body = compile_statement(*fx.body);
				std::uint64_t remaining = fx.body->nested_alloc(); 
				const auto max_block_size = std::numeric_limits<std::uint8_t>::max();
				while(remaining != 0) {
					const auto block_size = static_cast<std::uint8_t>(std::min<std::uint64_t>(remaining, max_block_size));
					if(remaining == 1) {
						buf << inst::null();
					}
					else {
						buf << inst::alloc_local(block_size);
					}
					remaining-=block_size;
				}
				buf << body;
			}
			return buf;
		}



		InstructionBuffer compile_except(	
			const sst::misc::Except & except,
			const Label& label_except) {
			
			InstructionBuffer buf;
			buf << inst::label(label_except.to_string());
			buf << compile_body(except);
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
		
		buf << compile_body(fx);
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