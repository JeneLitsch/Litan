#include "compile.hxx"
#include <iostream>
#include "build_in.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer compile_body(const auto & fx) {
			InstructionBuffer buf;
			if(fx.body) {
				const auto body = compile_statement(*fx.body);
				for(std::size_t i = 0; i < fx.body->nested_alloc(); i++) {
					buf << inst::null();
				}
				buf << body;
			}
			return buf;
		}



		InstructionBuffer compile_except(	
			const sst::Except & except,
			const Label& label_except) {
			
			InstructionBuffer buf;
			buf << inst::label(label_except.to_string());
			buf << compile_body(except);
			buf << inst::null();
			buf << inst::retvrn();
			return buf;
		}



		InstructionBuffer compile_function(const sst::Function & fx) {
			
			InstructionBuffer buf;

			const auto except_label = derive_except(fx.label); 
			
			buf << inst::label(fx.label.to_string());
			if(fx.except) buf << inst::trY(except_label.to_string());
			buf << compile_body(fx);
			buf << inst::null();
			buf << inst::retvrn();
			if(fx.except) {
				buf << compile_except(*fx.except, except_label);
			} 
			
			return buf;
		}



		InstructionBuffer compile_build_in_function(const sst::BuildIn & fx) {
			InstructionBuffer buf;

			buf << inst::label(fx.label.to_string());
			buf << resolve_build_in(fx.key);
			buf << inst::retvrn();
			
			return buf;
		}
	}





	InstructionBuffer compile_functional(const sst::Functional & functional) {
		if(auto fx = as<const sst::Function>(functional)) {
			return compile_function(*fx);
		}
		if(auto fx = as<const sst::BuildIn>(functional)) {
			return compile_build_in_function(*fx);
		}
		throw std::runtime_error{"Unknown functional declaration"};
	}
}