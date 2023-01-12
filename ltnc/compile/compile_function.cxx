#include "compile.hxx"
#include <iostream>
#include "build_in/build_in.hxx"
#include "ltnc/print/print.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer compile_body(const auto & fx) {
			InstructionBuffer buf;
			if(fx.body) {
				const auto body = compile_statement(*fx.body);
				for(std::size_t i = 0; i < fx.body->local_vars; i++) {
					buf << inst::makevar();
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



		InstructionBuffer compile_function(
			const sst::Function & fx,
			std::optional<Label> override_label = std::nullopt) {
			
			InstructionBuffer buf;

			const auto label = override_label.value_or(fx.label);
			const auto except_label = derive_except(label); 
			
			buf << inst::label(label.to_string());
			if(fx.except) buf << inst::trY(except_label.to_string());
			buf << compile_body(fx);
			buf << inst::null();
			buf << inst::retvrn();
			if(fx.except) {
				buf << compile_except(*fx.except, except_label);
			} 
			
			return buf;
		}



		InstructionBuffer compile_build_in_function(
			const sst::BuildIn & fx,
			std::optional<Label> override_label) {

			const auto label = override_label.value_or(fx.label);
			
			InstructionBuffer buf;

			buf << inst::label(label.to_string());
			buf << resolve_build_in(fx.key);
			buf << inst::null();
			buf << inst::retvrn();
			
			return buf;
		}
	}



	InstructionBuffer compile_functional(
		const sst::Functional & functional,
		std::optional<Label> override_label) {

		if(auto fx = as<const sst::Function>(functional)) {
			return compile_function(*fx, override_label);
		}
		if(auto fx = as<const sst::BuildIn>(functional)) {
			return compile_build_in_function(*fx, override_label);
		}
		throw std::runtime_error{"Unknown functional declaration"};
	}



	InstructionBuffer compile_functional(const sst::Functional & functional) {
		return compile_functional(functional, std::nullopt);
	}



	InstructionBuffer compile_expr(const sst::Lambda & lm) {
		
		const auto & fx = *lm.fx;
		InstructionBuffer buf;

		const auto & label = fx.label;
		const auto label_skip = derive_skip(label);
		
		// Skip
		buf << inst::jump(label_skip.to_string());
		
		InstructionBuffer capture_buf;
		
		// compile function
		buf << compile_function(*lm.fx);

		// Create function pointer
		buf << inst::label(label_skip.to_string());
		buf << inst::newfx(label.to_string(), fx.parameters.size());
		
		// store captures
		for(const auto & capture : lm.captures) {
			buf << compile_expression(*capture);
			buf << inst::capture();
		}


		std::vector<type::Type> parameter_types;
		for(const auto & parameter : fx.parameters) {
			parameter_types.push_back(parameter.type);
		}

		return buf;
	}
}