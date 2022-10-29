#include "compile.hxx"
#include <string_view>
#include <iostream>
namespace ltn::c {
	namespace {

		InstructionBuffer add_member(CompilerInfo & info, const std::string & name,  const InstructionBuffer & init) {
			InstructionBuffer buf;
			buf << inst::duplicate();
			buf << init;
			buf << inst::swap();
			buf << inst::member_write(info.member_table.get_id(name));
			return buf;
		}


		InstructionBuffer add_name(CompilerInfo & info, const std::string & str) {
			return add_member(info, "name", InstructionBuffer{inst::newstr(str)});
		}



		InstructionBuffer add_function(CompilerInfo & info, const ast::Functional & fx) {
			InstructionBuffer buf;
			MajorScope scope{ast::Namespace{}, false, type::Any{}};
			ast::FxPointer fx_ptr {
				fx.name,
				fx.namespaze,
				fx.parameters.size(),
				SourceLocation{}
			};
			auto fx_ptr_code = compile_fxPointer(fx_ptr, info, scope).code;

			buf << inst::newstruct();
			buf << add_name(info, fx.name);
			buf << add_member(info, "fx_ptr", fx_ptr_code);
			
			return buf;
		}



		InstructionBuffer add_functions(CompilerInfo & info, const ast::Reflect::NamespaceQuery & query) {
			InstructionBuffer buf;
			
			std::size_t count = 0;
			for(const auto & fx : info.fx_table.get_symbols()) {
				if(fx->namespaze == query.namespaze) {
					buf << add_function(info, *fx);
					++count;
				}
			}
			buf << inst::newarr(count);

			return add_member(info, "functions", buf);
		}



		ExprResult compile_reflect_query(const ast::Reflect::NamespaceQuery & query, CompilerInfo & info, Scope & scope) {
			InstructionBuffer buf;
			buf << inst::newstruct();
			buf << add_name(info, query.namespaze.to_string());
			buf << add_functions(info, query);
			return {buf};
		}
	}



	// compiles array literal
	ExprResult compile_reflect(const ast::Reflect & refl, CompilerInfo & info, Scope & scope) {
		return std::visit([&] (const auto & query) {
			return compile_reflect_query(query, info, scope);
		}, refl.query);
	}
}