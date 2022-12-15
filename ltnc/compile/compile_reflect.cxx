#include "compile.hxx"
#include "stdxx/iife.hxx"
#include <string_view>
#include <iostream>
#include <filesystem>
namespace ltn::c {
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
			buf << add_member(addr.name, {
				inst::newstr(query.name)
			});
			buf << add_member(addr.full_name, {
				inst::newstr(query.full_name)
			});
			buf << add_member(addr.fx_ptr, {
				inst::newfx(query.id, query.arity)
			});
			buf << add_member(addr.c0nst, {
				query.c0nst ? inst::bool_true() : inst::bool_false()
			});

			buf << add_member(addr.pr1vate, {
				query.pr1vate ? inst::bool_true() : inst::bool_false()
			});

			buf << add_member(addr.ext3rn, {
				query.ext3rn ? inst::bool_true() : inst::bool_false()
			});
			return buf;
		}


		InstructionBuffer compile_reflect_query(
			const sst::Reflect::Addr & addr,
			const sst::Reflect::NamespaceQuery & query) {

			InstructionBuffer buf;
			buf << inst::newstruct();
			buf << add_member(addr.name, {
				inst::newstr(query.namespaze.to_string())
			});
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


		InstructionBuffer compile_reflect_query(
			const sst::Reflect::Addr & addr,
			const sst::Reflect::LineQuery & query) {

			InstructionBuffer buf;
			buf << inst::newi(static_cast<std::int64_t>(query.line));
			return buf;
		}


		InstructionBuffer compile_reflect_query(
			const sst::Reflect::Addr & addr,
			const sst::Reflect::FileQuery & query) {

			const auto path = std::filesystem::path{query.name};

			InstructionBuffer buf;
			buf << inst::newstruct();
			buf << add_member(addr.name, {
				inst::newstr(path.filename().string())
			});
			return buf;
		}


		InstructionBuffer compile_reflect_query(
			const sst::Reflect::Addr & addr,
			const sst::Reflect::LocationQuery & query) {

			InstructionBuffer buf;
			buf << inst::newstruct();
			buf << add_member(addr.line, compile_reflect_query(addr, query.line));
			buf << add_member(addr.file, compile_reflect_query(addr, query.file));
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