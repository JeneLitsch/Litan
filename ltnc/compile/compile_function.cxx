#include "compile.hxx"
#include <iostream>
#include "build_in/build_in.hxx"
#include "ltnc/print/print.hxx"

namespace ltn::c {
	namespace {

		const std::string jumpmark_except(const std::string_view name) {
			std::stringstream ss;
			ss << "_" << name << "_EXCEPT";
			return ss.str(); 
		}

		const std::string jumpmark_skip(const std::string_view name) {
			std::stringstream ss;
			ss << "_" << name << "_SKIP";
			return ss.str(); 
		}


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
			const std::string & fxid) {
			
			InstructionBuffer buf;
			buf << inst::label(jumpmark_except(fxid));
			buf << inst::parameters(1);
			buf << compile_body(except);
			buf << inst::null();
			buf << inst::retvrn();
			return buf;
		}

		// compiles Litan function
		InstructionBuffer compile_function(
			const sst::Function & fx,
			std::optional<std::string> override_id = std::nullopt) {
			
			InstructionBuffer buf;

			const auto id = override_id.value_or(fx.id);
			
			buf << inst::label(id);
			for(const auto & c : fx.capture) {
				buf << inst::makevar();
				buf << inst::write_x(c->addr);
				// buf << compile_expression(*c);
			}
			buf << inst::parameters(static_cast<std::uint8_t>(fx.parameters.size()));
			if(fx.except) buf << inst::trY(jumpmark_except(id));
			buf << compile_body(fx);
			buf << inst::null();
			buf << inst::retvrn();
			if(fx.except) {
				buf << compile_except(*fx.except, id);
			} 
			
			return buf;
		}




		// compiles asm_function
		InstructionBuffer compile_build_in_function(
			const sst::BuildIn & fx,
			std::optional<std::string> override_id) {
			
			InstructionBuffer buf;

			buf << inst::label(override_id.value_or(fx.id));
			buf << resolve_build_in(fx.key);
			buf << inst::null();
			buf << inst::retvrn();
			
			return buf;
		}
	}



	// compiles functional node
	InstructionBuffer compile_functional(
		const sst::Functional & functional,
		std::optional<std::string> override_id) {

		if(auto fx = as<const sst::Function>(functional)) {
			return compile_function(*fx, override_id);
		}
		if(auto fx = as<const sst::BuildIn>(functional)) {
			return compile_build_in_function(*fx, override_id);
		}
		throw std::runtime_error{"Unknown functional declaration"};
	}


	// compiles functional node
	InstructionBuffer compile_functional(const sst::Functional & functional) {
		return compile_functional(functional, std::nullopt);
	}



	InstructionBuffer compile_expr(const sst::Lambda & lm) {
		
		const auto & fx = *lm.fx;
		InstructionBuffer buf;
		
		// Skip
		buf << inst::jump(jumpmark_skip(fx.id));
		
		InstructionBuffer capture_buf;
		
		// compile function
		buf << compile_function(*lm.fx);

		// Create function pointer
		buf << inst::label(jumpmark_skip(fx.id));
		buf << inst::newfx(fx.id, fx.parameters.size());
		
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