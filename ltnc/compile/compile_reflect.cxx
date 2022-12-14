#include "compile.hxx"
#include "stdxx/iife.hxx"
#include <string_view>
#include <iostream>
namespace ltn::c {
	// namespace {




	// 	InstructionBuffer add_member_bool(
	// 		CompilerInfo & info,
	// 		const std::string & name,
	// 		bool value) {
			
	// 		return add_member(info, name, InstructionBuffer{
	// 			value ? inst::bool_true() : inst::bool_false()
	// 		});
	// 	}


	// 	InstructionBuffer add_member_string(
	// 		CompilerInfo & info,
	// 		const std::string & name,
	// 		const std::string & str) {
			
	// 		return add_member(info, name, InstructionBuffer{inst::newstr(str)});
	// 	}



	// 	InstructionBuffer reflect_function(
	// 		CompilerInfo & info,
	// 		const sst::Functional & fx) {

	// 		InstructionBuffer buf;
	// 		MajorScope scope{Namespace{}, false};
	// 		sst::FxPointer fx_ptr {
	// 			fx.name,
	// 			fx.namespaze,
	// 			fx.parameters.size(),
	// 			SourceLocation{}
	// 		};
	// 		auto fx_ptr_code = compile_expression(fx_ptr, info, scope).code;

	// 		buf << inst::newstruct();
	// 		buf << add_member_string(info, "name", fx.name);
	// 		buf << add_member(info, "fx_ptr", fx_ptr_code);
	// 		buf << add_member_bool(info, "const",  fx.c0nst);
	// 		buf << add_member_bool(info, "extern", fx.init);
			
	// 		return buf;
	// 	}



	// 	InstructionBuffer reflect_functions(
	// 		CompilerInfo & info,
	// 		const Namespace & namespaze) {

	// 		InstructionBuffer buf;
			
	// 		std::size_t count = 0;
	// 		for(const auto & fx : info.fx_table.get_symbols()) {
	// 			if(fx->namespaze == namespaze) {
	// 				buf << reflect_function(info, *fx);
	// 				++count;
	// 			}
	// 		}
	// 		buf << inst::newarr(count);

	// 		return add_member(info, "functions", buf);
	// 	}



	// 	InstructionBuffer reflect_globals(
	// 		CompilerInfo & info,
	// 		const Namespace & namespaze) {
			
	// 		InstructionBuffer buf;
			
	// 		std::size_t count = 0;
	// 		for(const auto & global : info.global_table.get_symbols()) {
	// 			if(global->namespaze == namespaze) {
	// 				buf << inst::newstruct();
	// 				buf << add_member_string(info, "name", global->name);
	// 				++count;
	// 			}
	// 		}
	// 		buf << inst::newarr(count);

	// 		return add_member(info, "globals", buf);
	// 	}


	namespace {
		InstructionBuffer add_member(const std::size_t addr,
			const InstructionBuffer & init) {
	
			InstructionBuffer buf;
			buf << inst::duplicate();
			buf << init;
			buf << inst::swap();
			buf << inst::member_write(addr);
			return buf;
		}

		InstructionBuffer compile_reflect_query(
			const sst::Reflect::Addr & addr,
			const sst::Reflect::FunctionQuery & query) {

			InstructionBuffer buf;
			buf << inst::newstruct();
			buf << add_member(addr.name, stx::iife([&] {
				InstructionBuffer buf;
				buf << inst::newstr(query.id);
				return buf;
			}));
			buf << add_member(addr.fx_ptr, stx::iife([&] {
				InstructionBuffer buf;
				buf << inst::newfx(query.id, query.arity);
				return buf;
			}));
			return buf;
		}


		InstructionBuffer compile_reflect_query(
			const sst::Reflect::Addr & addr,
			const sst::Reflect::NamespaceQuery & query) {

			InstructionBuffer buf;
			buf << inst::newstruct();
			buf << add_member(addr.name, stx::iife([&] {
				InstructionBuffer buf;
				buf << inst::newstr(query.namespaze.to_string());
				return buf;
			}));
			buf << add_member(addr.functions, stx::iife([&] {
				InstructionBuffer buf;
				for(const auto & fx : query.functions) {
					buf << compile_reflect_query(addr, fx);
				}
				buf << inst::newarr(query.functions.size());
				return buf;
			}));
			return buf;
		}
	}



	// compiles array literal
	InstructionBuffer compile_expr(const sst::Reflect & refl) {

		return std::visit([&] (const auto & query) {
			return compile_reflect_query(refl.addr, query);
		}, refl.query);
	}
}