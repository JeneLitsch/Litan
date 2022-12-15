#include "analyze.hxx"
#include <string_view>
#include <iostream>
namespace ltn::c {
	// namespace {

	// 	InstructionBuffer add_member(
	// 		CompilerInfo & info,
	// 		const std::string & name,
	// 		const InstructionBuffer & init) {
	
	// 		InstructionBuffer buf;
	// 		buf << inst::duplicate();
	// 		buf << init;
	// 		buf << inst::swap();
	// 		buf << inst::member_write(info.member_table.get_id(name));
	// 		return buf;
	// 	}


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
	// 		const ast::Functional & fx) {

	// 		InstructionBuffer buf;
	// 		MajorScope scope{Namespace{}, false};
	// 		sst::FxPointer fx_ptr {
	// 			fx.name,
	// 			fx.namespaze,
	// 			fx.parameters.size(),
	// 			SourceLocation{}
	// 		};
	// 		auto fx_ptr_code = analyze_expression(fx_ptr, info, scope).code;

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



	// 	sst::expr_ptr analyze_reflect_query(
	// 		const FunctionQuery & query,
	// 		CompilerInfo & info,
	// 		Scope & scope) {

	// 		InstructionBuffer buf;
	// 		auto fx = info.fx_table.resolve(query.name, scope.get_namespace(), query.namespaze, query.arity);
	// 		if(!fx) throw CompilerError {
	// 			"Undefined function " + query.namespaze.to_string() + query.name + " in reflection."
	// 		};
	// 		info.fx_queue.stage_function(*fx);
	// 		buf << reflect_function(info, *fx);
	// 		return {buf};
	// 	}


	// 	sst::expr_ptr analyze_reflect_query(
	// 		const NamespaceQuery & query,
	// 		CompilerInfo & info,
	// 		Scope &) {

	// 		InstructionBuffer buf;
	// 		buf << inst::newstruct();
	// 		buf << add_member_string(info, "name", query.namespaze.to_string());
	// 		buf << reflect_functions(info, query.namespaze);
	// 		buf << reflect_globals(info, query.namespaze);
	// 		return {buf};
	// 	}
	// }

	namespace {
		sst::Reflect::FunctionQuery analyze_reflect_query(
			const FunctionQuery & query,
			CompilerInfo & info) {

			const auto * fx = info.fx_table.resolve(
				query.name,
				query.namespaze,
				query.arity
			);

			if(!fx) {
				throw undefined_function(query.name, ast::Node{{}});
			}
			
			info.fx_queue.stage_function(*fx);

			sst::Reflect::FunctionQuery sst_query {
				.id = fx->id,
				.arity = fx->parameters.size(),
			};

			return sst_query;
		}



		sst::Reflect::NamespaceQuery analyze_reflect_query(
			const NamespaceQuery & query,
			CompilerInfo & info) {

			sst::Reflect::NamespaceQuery sst_query;
			sst_query.namespaze = query.namespaze;
			for(const auto & fx : info.fx_table.get_symbols()) {
				if(fx->namespaze == query.namespaze) {
					info.fx_queue.stage_function(*fx);
					sst_query.functions.push_back(sst::Reflect::FunctionQuery {
						.id = fx->id,
						.name = fx->name,
						.full_name = fx->namespaze.to_string() + fx->name,
						.arity = fx->parameters.size(),
					});
				}
			}
		
			return sst_query;
		}
	}



	// compiles array literal
	sst::expr_ptr analyze_expr(
		const ast::Reflect & refl,
		CompilerInfo & info,
		Scope &) {
			
		return std::make_unique<sst::Reflect>(
			std::visit([&] (const auto & query) -> sst::Reflect::Query {
				return analyze_reflect_query(query, info);
			}, refl.query),
			sst::Reflect::Addr {
				.name = info.member_table.get_id("name"),
				.full_name = info.member_table.get_id("full_name"),
				.fx_ptr = info.member_table.get_id("fx_ptr"),
				.functions = info.member_table.get_id("functions"),
			},
			type::Null{}
		);
	}
}