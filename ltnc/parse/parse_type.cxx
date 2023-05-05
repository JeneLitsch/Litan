#include "parse.hxx"


namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::type_ptr parse_type_name(const Token & begin, Tokens & tokens);



		template<typename T>
		ast::type_ptr simple_type(const Token & begin) {
			const auto & loc = begin.location;
			return std::make_unique<ast::Type>(T{}, loc); 
		}



		ast::type_ptr array_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				auto sub_type = parse_type_name(begin, tokens);
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};
				return std::make_unique<ast::Type>(ast::Type::Array{
					.contains = std::move(sub_type),
				}, loc);
			}
			else {
				return std::make_unique<ast::Type>(ast::Type::Array{
					.contains = nullptr,
				}, loc); 
			}
		}


		ast::type_ptr parse_type_name(const Token & begin, Tokens & tokens) {
			if(auto name = match(TT::INDENTIFIER, tokens)) {
				if(name->str == "null") return simple_type<ast::Type::Null>(begin);
				if(name->str == "bool") return simple_type<ast::Type::Bool>(begin);
				if(name->str == "char") return simple_type<ast::Type::Char>(begin);
				if(name->str == "int") return simple_type<ast::Type::Int>(begin);
				if(name->str == "float") return simple_type<ast::Type::Float>(begin);
				if(name->str == "string") return simple_type<ast::Type::String>(begin);
				if(name->str == "array") return array_type(begin, tokens);
				throw CompilerError {"Unknown type name " + name->str, name->location};
			}
			throw CompilerError {"Expected type name", begin.location};
		}
	}



	ast::type_ptr parse_type(Tokens & tokens) {
		if(auto begin = match(TT::SMALLER, tokens)) {
			auto type = parse_type_name(*begin, tokens);
			if(!match(TT::BIGGER, tokens)) throw CompilerError {
				"Expected )", begin->location
			};
			return type;
		}
		else return nullptr;
	}
}