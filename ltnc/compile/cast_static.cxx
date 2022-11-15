#include <sstream>
#include <iostream>
#include "stdxx/array.hxx"
#include "stdxx/iife.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/compile/cast_static.hxx"
#include "ltnc/compile/cast_utils.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		std::vector<std::uint8_t> to_type_code(
			const type::Type &,
			const type::Type &,
			const SourceLocation &);



		std::vector<std::uint8_t> cast_to(
			const type::Type &,
			const type::Bool &,
			const SourceLocation &) {
			return { type_code::BOOL };
		}



		std::vector<std::uint8_t> cast_to(
			const type::Type & from,
			const type::Char & to,
			const SourceLocation & location) {
			
			if(type::is_numeric(from)) return { type_code::CHAR };
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to(
			const type::Type & from,
			const type::Int & to,
			const SourceLocation & location) {
			if(type::is_numeric(from)) {
				return {type_code::INT };
			} 
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to(
			const type::Type & from,
			const type::Float & to,
			const SourceLocation & location) {
			
			if(type::is_numeric(from)) return { type_code::FLOAT };
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to(
			const type::Type & from,
			const type::String & to,
			const SourceLocation & location) {

			if(type::is_array(from)) {
				const auto & from_contained = from.as<type::Array>()->contains;
				
				if(!from_contained) return {
					type_code::STRING
				};

				if(type::is_numeric(**from_contained)) return {
					type_code::STRING
				};
			}
			
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to(
			const type::Type & from,
			const type::Array & to,
			const SourceLocation & location) {
			if(type::is_array(from)) {
				// Allows casting empty array to any other array type
				const type::Type & from_contained = stx::iife([&] {
					auto * arr = from.as<type::Array>();
					if(arr->contains) {
						return **arr->contains;
					}
					else {
						return **to.contains;
					}
				});
				auto x = to_array_of(to_type_code(from_contained, **to.contains, location)); 
				return x;
			}
			if(type::is_string(from)) {
				if(type::is_numeric(**to.contains)) {
					// Cast string like an array<char>
					return to_array_of(to_type_code(type::Char{}, **to.contains, location)); 
				}
			}
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to(
			const type::Type & from,
			const auto & to,
			const SourceLocation & location) {
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> to_type_code(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			return to.visit([&] (auto & type) { 
				return cast_to(from, type, location);
			});
		}
	}



	InstructionBuffer cast_static(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		if(from == to) return {};
		InstructionBuffer buf;
		buf << inst::cast(to_type_code(from, to, location));
		return buf;
	}
}