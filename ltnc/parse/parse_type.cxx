#include "parse.hxx"
#include "parse_utils.hxx"

namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::type_ptr parse_type_name(const Token & begin, Tokens & tokens);



		template<typename T>
		ast::type_ptr simple_type(const Token & begin) {
			const auto & loc = begin.location;
			return std::make_unique<ast::expr::Type>(T{}, loc); 
		}




		template<typename T>
		ast::type_ptr unary_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				auto sub_type = parse_type_name(begin, tokens);
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};
				return std::make_unique<ast::expr::Type>(T{
					.contains = std::move(sub_type),
				}, loc);
			}
			else {
				return std::make_unique<ast::expr::Type>(T{
					.contains = nullptr,
				}, loc); 
			}
		}



		ast::type_ptr tuple_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				if(match(TT::PAREN_R, tokens)) {
					return std::make_unique<ast::expr::Type>(ast::expr::Type::TupleN{
						.contains = {},
					}, loc);
				}
				std::vector<ast::type_ptr> sub_types;
				do {
					sub_types.push_back(parse_type_name(begin, tokens));
				} while(match(TT::COMMA, tokens));
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};
				return std::make_unique<ast::expr::Type>(ast::expr::Type::TupleN{
					.contains = std::move(sub_types),
				}, loc);
			}
			else {
				return std::make_unique<ast::expr::Type>(ast::expr::Type::Tuple{}, loc); 
			}
		}



		ast::type_ptr map_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				auto key = parse_type_name(begin, tokens);
				if(!match(TT::COMMA, tokens)) throw CompilerError {
					"Expected ,", loc
				};
				auto val = parse_type_name(begin, tokens);
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};
				return std::make_unique<ast::expr::Type>(ast::expr::Type::Map{
					.key = std::move(key),
					.value = std::move(val),
				}, loc);
			}
			else {
				return std::make_unique<ast::expr::Type>(ast::expr::Type::Map{
					.key = nullptr,
					.value = nullptr,
				}, loc); 
			}
		}


		ast::type_ptr fx_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				auto token_arity = match(TT::INTEGER, tokens);
				if(!token_arity) throw CompilerError {
					"Expected arity", loc
				};
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};

				std::stringstream iss{token_arity->str};
				std::uint64_t arity;
				iss >> arity;
				return std::make_unique<ast::expr::Type>(ast::expr::Type::FxN{
					.arity = arity,
				}, loc);
			}
			else {
				return std::make_unique<ast::expr::Type>(ast::expr::Type::Fx {}, loc); 
			}
		}



		std::variant<std::string, MemberCode> parse_struct_member_name(const Token & begin, Tokens & tokens) {
			if(auto name = match(TT::INDENTIFIER, tokens)) {
				return name->str;
			}
			else if(match(TT::BRACE_L, tokens)) {
				auto code = parse_member_code(tokens);

				if(!match(TT::BRACE_R, tokens)) {
					throw CompilerError{"Expected }", location(tokens)};
				}

				return code;
			}
			throw CompilerError{"Expected member", begin.location};
		}



		ast::type_ptr parse_struct_member_type(const Token & begin, Tokens & tokens) {
			if(auto new_begin = match(TT::COLON, tokens)) {
				return parse_type_name(*new_begin, tokens);
			}

			return std::make_unique<ast::expr::Type>(ast::expr::Type::Any{}, begin.location);
		}



		ast::expr::Type::Struct::Member parse_struct_member(const Token & begin, Tokens & tokens) {
			if(!match(TT::DOT, tokens)) {
				throw CompilerError{"Expected .", location(tokens)};
			}
			auto name = parse_struct_member_name(begin, tokens);
			auto type = parse_struct_member_type(begin, tokens);

			return ast::expr::Type::Struct::Member{
				.name = std::move(name),
				.type = std::move(type),
			};
		}



		ast::type_ptr parse_struct_type(const Token & begin, Tokens & tokens) {
			if(match(TT::PAREN_L, tokens)) {
				auto members = list_of<ast::expr::Type::Struct::Member>(TT::PAREN_R, ")", tokens, [&begin] (auto & tokens) {
					return parse_struct_member(begin, tokens);
				});
				return std::make_unique<ast::expr::Type>(ast::expr::Type::Struct{
					.members = std::move(members),
				}, begin.location);
			}
			else {
				return simple_type<ast::expr::Type::Struct>(begin);
			}
		}


		ast::type_ptr parse_type_name(const Token & begin, Tokens & tokens) {
			if(auto name = match(TT::NVLL, tokens)) {
				return simple_type<ast::expr::Type::Null>(begin);
			}
			if(auto name = match(TT::INDENTIFIER, tokens)) {
				if(name->str == "any") return simple_type<ast::expr::Type::Any>(begin);
				if(name->str == "bool") return simple_type<ast::expr::Type::Bool>(begin);
				if(name->str == "char") return simple_type<ast::expr::Type::Char>(begin);
				if(name->str == "int") return simple_type<ast::expr::Type::Int>(begin);
				if(name->str == "float") return simple_type<ast::expr::Type::Float>(begin);
				if(name->str == "string") return simple_type<ast::expr::Type::String>(begin);
				if(name->str == "array") return unary_type<ast::expr::Type::Array>(begin, tokens);
				if(name->str == "tuple") return tuple_type(begin, tokens);
				if(name->str == "fx") return fx_type(begin, tokens);
				if(name->str == "istream") return simple_type<ast::expr::Type::IStream>(begin);
				if(name->str == "ostream") return simple_type<ast::expr::Type::OStream>(begin);
				if(name->str == "iter") return simple_type<ast::expr::Type::Iterator>(begin);
				if(name->str == "stop") return simple_type<ast::expr::Type::IteratorStop>(begin);
				if(name->str == "rng") return simple_type<ast::expr::Type::Rng>(begin);
				if(name->str == "clock") return simple_type<ast::expr::Type::Clock>(begin);
				if(name->str == "type") return simple_type<ast::expr::Type::TypeT>(begin);
				if(name->str == "queue") return unary_type<ast::expr::Type::Queue>(begin, tokens);
				if(name->str == "stack") return unary_type<ast::expr::Type::Stack>(begin, tokens);
				if(name->str == "map") return map_type(begin, tokens);
				if(name->str == "struct") return parse_struct_type(begin, tokens);
				throw CompilerError {"Unknown type name " + name->str, name->location};
			}
			throw CompilerError {"Expected type name", begin.location};
		}




		ast::type_ptr parse_type_name_start(const Token & begin, Tokens & tokens) {
			if(auto name = match("type", tokens)) {
				if(match(TT::COLON, tokens)) {
					return parse_type_name(begin, tokens);
				}
				else {
					return simple_type<ast::expr::Type::TypeT>(begin);
				}
			}
			return parse_type_name(begin, tokens);
		}
	}



	ast::type_ptr parse_type(Tokens & tokens) {
		if(auto begin = match(TT::SMALLER, tokens)) {
			auto type = parse_type_name_start(*begin, tokens);
			if(!match(TT::BIGGER, tokens)) throw CompilerError {
				"Expected >", begin->location
			};
			return type;
		}
		else return nullptr;
	}
}